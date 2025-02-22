#include <bits/stdc++.h>
#include "defineSDL.hpp"
using namespace  std;

int main(int argc, char* argv[]){
    const int FPS = 60;
    const int FrameDelay = 1000/60;
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
    SDL_Texture* runningRight;
    SDL_Texture* runningLeft;
    runningRight = IMG_LoadTexture(render,"C:/Users/game/res/image/RUNRIGHT.png");
    runningLeft = IMG_LoadTexture(render,"C:/Users/game/res/image/RUNLEFT.png");
    SDL_Texture* attack;
    attack = IMG_LoadTexture(render,"C:/Users/game/res/image/ATTACK 1.png");
    if (!texture) {
        cout << "Lỗi tải ảnh: " << IMG_GetError() << endl;
        return -1;
    }
    float jumpSpeed0 = 0;
    float gravity = 0.5;
    float jumpSpeed = -10;
    
    bool gamerunning = true;
    character run(vector2d(200, 510), runningRight, 7);
    bool isJumping = false;
    bool isJump = false;
    while(gamerunning){
        if(isJumping){
            run.pos.y += jumpSpeed0;
            jumpSpeed0 += gravity;
        }
        if(run.pos.y>=510){
            isJumping = false;
            run.pos.y=510;
            jumpSpeed0 = 0;
        }
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gamerunning = false;
            }else if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                    run.ismoving = true;
                    run.pos.x -= 10;
                    run.tex = runningLeft;
                    break;
                    case SDLK_RIGHT:
                    run.ismoving = true;
                    run.pos.x += 10;
                    run.tex = runningRight;
                    break;
                    case SDLK_SPACE:
                    if(!isJumping){
                       
                            isJumping = true;
                            jumpSpeed0 = jumpSpeed;
                        
                    }
                    switch(event.key.keysym.sym){
                        case SDLK_LEFT:
                        run.ismoving = true;
                        run.pos.x -= 10;
                        run.tex = runningLeft;
                        break;
                        case SDLK_RIGHT:
                        run.ismoving = true;
                        run.pos.x += 10;
                        run.tex = runningRight;
                        break;}
                    break;
                    case SDLK_q:
                    run.isAttacking = true;
                    run.tex = attack;
                    break;
                }
            }else if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                    run.ismoving = false;
                    break;
                    case SDLK_RIGHT:
                    run.ismoving = false;
                    break;
                    case SDLK_q:
                    run.isAttacking = false;
                    break;
                }
            }run.Physic();
        }
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime > lastFrameTime + FrameDelay) {
            if (!run.isAttacking) {
                run.UpdateRunFrame();
            } else {
                run.UpdateAttackFrame();
            }
            lastFrameTime = currentTime;
        }
        SDL_RenderClear(render);
        SDL_RenderCopy(render,background,NULL,NULL);
        for(entity & i : road){
            SDL_Rect source = {i.currentFrame.x, i.currentFrame.y, i.currentFrame.w, i.currentFrame.h};
            SDL_Rect dest = {i.pos.x,i.pos.y,i.currentFrame.w, i.currentFrame.h};
            SDL_RenderCopy(render,i.tex,&source,&dest);
        }
        SDL_Rect charDest = {run.pos.x, run.pos.y,run.currentFrame.w,run.currentFrame.h};
        SDL_RenderCopy(render, run.tex, &run.currentFrame, &charDest);
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