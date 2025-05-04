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
    SDL_Texture* GameOver;
    GameOver = IMG_LoadTexture(render,"C:/Users/game/res/image/GameOver.png");
    SDL_Texture* VICTORY;
    VICTORY = IMG_LoadTexture(render,"C:/Users/game/res/image/VICTORY.png");
    Uint32 lastFrameUpdate = 0;
    Uint32 lastbitetime = 0;
    const int animationDelay = 100;
    bool gamerunning = true;
    int level  = 1;
    vector<Enemy> enemies;
    int enemyspawn = 1;
    character action(vector2d(200, 450), runningRight, 7);
    for(int i = 0; i < enemyspawn; i++) {
        int x = 100 + rand() % 1000; // vị trí random
        int y = 100 + rand() % 300;
        enemies.push_back(Enemy(vector2d(x, y), enemyflyleft, 4));
    }
    bool Victory = false;
    while(gamerunning){
        bool allenemiesisdead = true;
        action.jumpPhysic();
        action.MovingRight();
        action.MovingLeft();
            double Distance;
            double DistanceX;
            double DistanceY;
            for(Enemy &enemy : enemies){
                if(enemy.isDead){
                    continue;
                }
                allenemiesisdead = false;
            float PlayerCenterX = action.pos.x + (action.currentFrame.w * 1.5) / 2.0;
            float PlayerCenterY = action.pos.y + (action.currentFrame.h * 1.5) / 2.0;
            float EnemyCenterX = enemy.pos.x + enemy.enemycurrentFrame.w / 2.0;
            float EnemyCenterY = enemy.pos.y + enemy.enemycurrentFrame.h / 2.0;
            DistanceX = PlayerCenterX - EnemyCenterX;
            DistanceY = PlayerCenterY - EnemyCenterY;
            Distance = sqrt((DistanceX*DistanceX)+(DistanceY*DistanceY));
            if(Distance < 1000){
                enemy.isnearplayer = true;
            }else{
                enemy.isnearplayer = false;
            }
        if(enemy.isnearplayer){
            if(abs(DistanceX)>40){
                if(DistanceX>40){
                    enemy.pos.x += 2;
                    enemy.isLeft = false;
                    enemy.isRight = true;
                }else if(DistanceX<-40){
                    enemy.pos.x -= 2;
                    enemy.isRight = false;
                    enemy.isLeft = true;
                }
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
        if(Distance <=60 && !enemy.isDead){
            enemy.enemyAttack = true;
            enemy.isFlying = false;
            action.isHurt = true;
        }else{
            enemy.enemyAttack = false;
            enemy.isFlying = true;
            action.isHurt = false;
        }
        if(enemy.enemyAttack){
            if(enemy.isRight){
                enemy.tex = enemyattackright;
            }else if(enemy.isLeft) {
                enemy.tex = enemyattackleft;
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
        if(action.isAttacking && Distance<100 && !enemy.isDead){
            bool enemyinfront = (action.isFacingRight&&PlayerCenterX < EnemyCenterX)||(!action.isFacingRight&&PlayerCenterX > EnemyCenterX);
            if(enemyinfront){
                enemy.enemyAttack = false;
            enemy.getHitCnt++;
            if(enemy.getHitCnt == enemy.lastHitCnt){
                enemy.isDead = true;
            }
            if(action.pos.x > enemy.pos.x){
                enemy.tex = enemyHurtRight;
                enemy.pos.x -=100;
            }else if(action.pos.x < enemy.pos.x){
                enemy.tex = enemyHurtLeft;
                enemy.pos.x +=100;
            }
            }
        }
        if (enemy.isFlying){
            enemy.updateFlyframe();
        }
            }
            if (allenemiesisdead) {
                if(level>=5){
                    Victory = true;
                }
                level++;
                enemyspawn += 2;
                enemies.clear();
                for(int i = 0; i < enemyspawn; i++) {
                    int x = 100 + rand() % 1000;
                    int y = 100 + rand() % 300;
                    enemies.push_back(Enemy(vector2d(x, y), enemyflyleft, 4));
                }
            }
            if (action.pos.x < 0) {action.pos.x = 0;}
            if (action.pos.x + action.currentFrame.w * 1.5 > 1285){
                action.pos.x = 1285 - action.currentFrame.w * 1.5;}
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
            } else if (action.isHurt) {
                action.donothing = false;
                if(action.isFacingRight){
                    action.tex = playerHurtRight;
                }else{
                    action.tex = playerHurtLeft;
                }
                if (action.isFacingRight) {
                    action.tex = playerHurtRight;
                } else {
                    action.tex = playerHurtLeft;
                }
                action.UpdateHurtFrame();
            } else if (action.isMovingLeft || action.isMovingRight) {
                action.UpdateRunFrame();
            } else {
                action.donothing = true;
                action.UpdateIdleFrame();
                if (action.isFacingRight) {
                    action.tex = idleright;
                } else {
                    action.tex = idleleft;
                }
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
        if(!action.isDead){
            SDL_RenderCopy(render, action.tex, &action.currentFrame, &charDest);
        }
        SDL_Rect HPback = {20,20,200,20};
        SDL_SetRenderDrawColor(render, 50, 50, 50, 255);
        SDL_RenderFillRect(render, &HPback);
        SDL_Rect HPfront = {20,20,(int)((float)action.HP /100*200),20};
        SDL_SetRenderDrawColor(render,200,0,0,255);
        SDL_RenderFillRect(render,&HPfront);
        for (Enemy& enemy : enemies) {
            if (!enemy.isDead) {
                SDL_Rect eneDest = {enemy.pos.x, enemy.pos.y, enemy.enemycurrentFrame.w, enemy.enemycurrentFrame.h};
                SDL_RenderCopy(render, enemy.tex, &enemy.enemycurrentFrame, &eneDest);
            }
        }
        if (action.isDead) {
            SDL_Rect gameOverDest = {0, 0, 1285, 700};
            SDL_RenderCopy(render, GameOver, NULL, &gameOverDest);
            SDL_RenderPresent(render);
            bool gameOver = true;
    SDL_Event e;
    while (gameOver) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                gamerunning = false;
                gameOver = false;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_b) {
                    action.pos = vector2d(200, 450);
                    action.HP = 100;
                    action.isDead = false;
                    action.isHurt = false;
                    action.isAttacking = false;
                    action.isMovingLeft = false;
                    action.isMovingRight = false;
                    action.count = 0;
                    enemies.clear();
                    enemyspawn = 1;
                    for (int i = 0; i < enemyspawn; i++) {
                        int x = 100 + rand() % 1000;
                        int y = 100 + rand() % 300;
                        enemies.push_back(Enemy(vector2d(x, y), enemyflyleft, 4));
                    }
                    level = 1;
                    gamerunning = true;
                    gameOver = false;
                }
            }
        }
    }
        }
        if (Victory) {
            SDL_Rect victoryRect = {0, 0, 1285, 700};
            SDL_RenderCopy(render, VICTORY, NULL, &victoryRect);
            SDL_RenderPresent(render);
            SDL_Event e;
            bool wait = true;
            while (wait) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        gamerunning = false;
                        wait = false;
                    } else if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_b) {
                            // Reset game
                            action.pos = vector2d(200, 450);
                            action.HP = 100;
                            action.isDead = false;
                            action.isHurt = false;
                            action.isAttacking = false;
                            action.isMovingLeft = false;
                            action.isMovingRight = false;
                            action.count = 0;
                            enemies.clear();
                            level = 1;
                            enemyspawn = 1;
                            Victory = false;
                            for (int i = 0; i < enemyspawn; i++) {
                                int x = 100 + rand() % 1000;
                                int y = 100 + rand() % 300;
                                enemies.push_back(Enemy(vector2d(x, y), enemyflyleft, 4));
                            }
                            wait = false;
                        }
                    }
                }
            }
            continue;
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