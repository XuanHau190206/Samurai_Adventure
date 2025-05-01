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
    SDL_Texture* playerHurtRight;
    playerHurtRight = IMG_LoadTexture(render,"C:/Users/game/res/image/HURTRIGHT.png");
    SDL_Texture* playerHurtLeft;
    playerHurtLeft = IMG_LoadTexture(render,"C:/Users/game/res/image/HURTLEFT.png");
    SDL_Texture* enemyflyleft;
    enemyflyleft = IMG_LoadTexture(render,"C:/Users/game/res/image/FLYINGLEFT.png");
    SDL_Texture* enemyflyright;
    enemyflyright = IMG_LoadTexture(render,"C:/Users/game/res/image/FLYINGRIGHT.png");
    SDL_Texture* enemyattackright;
    enemyattackright = IMG_LoadTexture(render,"C:/Users/game/res/image/enemyattackright.png");
    SDL_Texture* enemyattackleft;
    enemyattackleft = IMG_LoadTexture(render,"C:/Users/game/res/image/enemyattackleft.png");
    SDL_Texture* enemyHurtRight;
    enemyHurtRight = IMG_LoadTexture(render,"C:/Users/game/res/image/enemyHurtRight.png");
    SDL_Texture* enemyHurtLeft;
    enemyHurtLeft = IMG_LoadTexture(render,"C:/Users/game/res/image/enemyHurtLeft.png");
    SDL_Texture* HPbar;
    HPbar = IMG_LoadTexture(render,"C:/Users/game/res/image/HPBAR.png");
    Uint32 lastFrameUpdate = 0;
    Uint32 lastbitetime = 0;
    const int animationDelay = 100;
    bool gamerunning = true;
    character action(vector2d(200, 450), runningRight, 7);
    Enemy enemy(vector2d(200,200),enemyflyleft,4);
    while(gamerunning){
        action.jumpPhysic();
        action.MovingRight();
        action.MovingLeft();
            double Distance;
            double DistanceX;
            double DistanceY;
            DistanceX = action.pos.x-enemy.pos.x + 26;
            DistanceY = action.pos.y-enemy.pos.y + 60;
            Distance = sqrt((DistanceX*DistanceX)+(DistanceY*DistanceY));
            if(Distance < 300){
                enemy.isnearplayer = true;
            }else{
                enemy.isnearplayer = false;
            }
        if(action.donothing){
            if(action.isFacingRight){
                action.tex = idleright;
            }else{
                action.tex = idleleft;
            }
        }

        if(enemy.isnearplayer){
            if(DistanceX>0){
                enemy.pos.x += 2;
                enemy.isLeft = false;
                enemy.isRight = true;
            }else if(DistanceX<0){
                enemy.pos.x -= 2;
                enemy.isRight = false;
                enemy.isLeft = true;
            }
            if(DistanceY>0){
                enemy.pos.y += 2;
            }else if(DistanceY<0){
                enemy.pos.y -= 2;
            }
            if(enemy.isRight){
                enemy.tex = enemyflyright;
            }else if(enemy.isLeft){
                enemy.tex = enemyflyleft;
            }
        }
        if(Distance == 0 && !enemy.isDead){
            enemy.enemyAttack = true;
            action.isHurt = true;
        }else{
            enemy.enemyAttack = false;
            action.isHurt = false;
        }
        if(action.isHurt){
            action.UpdateHurtFrame();
        }
        if(enemy.enemyAttack){
            if(enemy.isRight){
                enemy.tex = enemyattackright;
            }else if(enemy.isLeft) {
                enemy.tex = enemyattackleft;
                
            }
            if(action.isFacingRight){
                action.tex = playerHurtRight;
            }else{
                action.tex = playerHurtLeft;
            }
            enemy.attackPlayer();
        }
        Uint32 bitecooldown = 1000;
        Uint32 now = SDL_GetTicks();
        if(enemy.enemyAttack&&now - lastbitetime > bitecooldown){
            action.HP -= 10;
            if(action.HP == 0){
                action.isDead = true;
            }
            lastbitetime = now;
        }
        if(action.isAttacking && Distance<=70 && !enemy.isDead){
            enemy.enemyAttack = false;
            enemy.getHitCnt++;
            if(enemy.getHitCnt == enemy.lastHitCnt){
                enemy.isDead = true;
            }
            if(action.pos.x > enemy.pos.x){
                enemy.tex = enemyHurtRight;
                enemy.pos.x -=70;
            }else if(action.pos.x < enemy.pos.x){
                enemy.tex = enemyHurtLeft;
                enemy.pos.x +=70;
            }
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
                    action.donothing = true;
                    break;
                    case SDLK_RIGHT:
                    action.isMovingRight = false;
                    action.donothing = true;
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
                action.UpdateIdleFrame();
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
        SDL_Rect charDest = {action.pos.x, action.pos.y,action.currentFrame.w*1.5,action.currentFrame.h*1.5};
        SDL_Rect eneDest = {enemy.pos.x, enemy.pos.y,enemy.enemycurrentFrame.w,enemy.enemycurrentFrame.h};
        if(!action.isDead){
            SDL_RenderCopy(render, action.tex, &action.currentFrame, &charDest);
        }
        if(!enemy.isDead){
            SDL_RenderCopy(render,enemy.tex,&enemy.enemycurrentFrame,&eneDest);
        }
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