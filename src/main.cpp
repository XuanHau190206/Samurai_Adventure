#include <bits/stdc++.h>
#include "defineSDL.hpp"
using namespace  std;
int main(int argc, char* argv[]){
    Uint32 lastFrameTime = SDL_GetTicks();
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_Window * window;
    window = SDL_CreateWindow("First Game",10,10,1285,700,0);
    SDL_Renderer * render;
    render = SDL_CreateRenderer(window,-1,0);
    SDL_Event event;
    SDL_Texture* background;
    background = IMG_LoadTexture(render,"C:/Users/game/res/image/1138740.png");
    SDL_Texture * texture;
    texture = IMG_LoadTexture(render,"C:/Users/game/res/image/Screenshot 2025-02-16 202642.png");
    vector<entity> road = { entity(vector2d(0,500), texture),
                            entity(vector2d(581,500), texture),
                            entity(vector2d(581*2,500), texture)};
    SDL_Texture* idleright;
    idleright = IMG_LoadTexture(render,"C:/Users/game/res/image/IDLERIGHT.png");
    SDL_Texture* idleleft;
    idleleft = IMG_LoadTexture(render,"C:/Users/game/res/image/IDLELEFT.png");
    SDL_Texture* runningRight;
    runningRight = IMG_LoadTexture(render,"C:/Users/game/res/image/RUNRIGHT.png");
    SDL_Texture* runningLeft;
    runningLeft = IMG_LoadTexture(render,"C:/Users/game/res/image/RUNLEFT.png");
    SDL_Texture* attackRight;
    attackRight = IMG_LoadTexture(render,"C:/Users/game/res/image/ATTACKRIGHT.png");
    SDL_Texture* attackLeft;
    attackLeft = IMG_LoadTexture(render,"C:/Users/game/res/image/ATTACKLEFT.png");
    SDL_Texture* enemyfly;
    enemyfly = IMG_LoadTexture(render,"C:/Users/game/res/image/FLYING.png");
    Uint32 lastFrameUpdate = 0;
    const int animationDelay = 100;
    bool gamerunning = true;
    character action(vector2d(200, 510), runningRight, 7);
    Enemy enemy(vector2d(200,200),enemyfly,4);
    while(gamerunning){
        action.jumpPhysic();
        action.MovingRight();
        action.MovingLeft();
        if(action.isFacingRight){
            action.tex = idleright;
        }else{
            action.tex = idleleft;
        }
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gamerunning = false;
            }else if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                    action.isMovingLeft = true;
                    action.isFacingRight = false;
                    action.donothing = false;
                    action.tex = runningLeft;
                    break;
                    case SDLK_RIGHT:
                    action.isMovingRight = true;
                    action.isFacingRight = true;
                    action.donothing = false;
                    action.tex = runningRight;
                    break;
                    case SDLK_SPACE:
                    action.jump();
                    break;
                    case SDLK_q:
                    action.isAttacking = true;
                    action.donothing = false;
                    if(action.isFacingRight){
                        action.tex = attackRight;
                    }else{
                        action.tex = attackLeft;
                    }
                    break;
                }
            }else if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                    action.isMovingLeft = false;
                    break;
                    case SDLK_RIGHT:
                    action.isMovingRight = false;
                    break;
                    case SDLK_q:
                    break;
                }
            }
        }
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime > lastFrameTime + FrameDelay) {
            if (action.isAttacking) {
                action.UpdateAttackFrame();
            } else if(action.isMovingLeft||action.isMovingRight) {
                action.UpdateRunFrame();
            }else if(action.donothing) {
                
            }
            if (enemy.isFlying){
                enemy.updateFlyframe();
            }
            lastFrameTime = currentTime;
        }
        SDL_Delay(FrameDelay);
        SDL_RenderClear(render);
        SDL_RenderCopy(render,background,NULL,NULL);
        for(entity & i : road){
            SDL_Rect source = {i.currentFrame.x, i.currentFrame.y, i.currentFrame.w, i.currentFrame.h};
            SDL_Rect dest = {i.pos.x,i.pos.y,i.currentFrame.w, i.currentFrame.h};
            SDL_RenderCopy(render,i.tex,&source,&dest);
        }
        SDL_Rect charDest = {action.pos.x, action.pos.y,action.currentFrame.w,action.currentFrame.h};
        SDL_Rect eneDest = {enemy.pos.x, enemy.pos.y,enemy.currentFrame.w,enemy.currentFrame.h};
        SDL_RenderCopy(render, action.tex, &action.currentFrame, &charDest);
        SDL_RenderCopy(render,enemy.tex,&enemy.currentFrame,&eneDest);
        SDL_RenderPresent(render);
    }
    
    SDL_Quit();
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    return 0;
}