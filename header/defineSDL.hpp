#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
#include "const.hpp"
using namespace std;
struct vector2d
{
    int x = 0;
    int y = 0;
    vector2d() {}
    vector2d(int X,int Y){
        x = X;
        y = Y;
    }
    void print(){
        cout<<x<<" "<<y;
    }
};
struct Enemy{
    vector2d pos;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
    int FrameCount;
    int FrameIndex;
    bool isFlying = true;
    Uint32 lastFrameUpdate = 0;
    const int animationDelay = 100;
    Enemy(vector2d POS,SDL_Texture *Tex,int frames){
        pos = POS;
        tex = Tex;
        FrameCount = frames;
        FrameIndex = 0;
        currentFrame.x = 0;
        currentFrame.y = 0;
        currentFrame.w = 50;
        currentFrame.h = 71;
    };
    void updateFlyframe (){
        Uint32 currentTime = SDL_GetTicks();
        if(isFlying){
            if (currentTime > lastFrameUpdate + animationDelay) {
                FrameIndex = (FrameIndex + 1) % FrameCount;
                currentFrame.x = FrameIndex * currentFrame.w;
                lastFrameUpdate = currentTime;
            }
        }
    }
};
struct character {
    vector2d pos;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
    int FrameCount;
    int FrameIndex;
    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isJumping = false;
    bool isAttacking = false;
    float jumpSpeed0 = 0;
    float gravity = 0.5;
    float jumpSpeed = -10;
    float speed = 10;
    int count = 0;
    Uint32 lastFrameUpdate = 0;
    const int animationDelay = 100;
    character(vector2d POS,SDL_Texture *Tex,int frames){
        pos = POS;
        tex = Tex;
        FrameCount = frames;
        FrameIndex = 0;
        currentFrame.x = 0;
        currentFrame.y = 0;
        currentFrame.w = 100;
        currentFrame.h = 100;
        
    };
    void MovingLeft(){
        if(isMovingLeft){
            pos.x -= speed;
        }
    }
    void MovingRight(){
        if(isMovingRight){
            pos.x += speed;
        }
    }
    void jump(){
        if(!isJumping){
            isJumping = true;
            jumpSpeed0 = jumpSpeed;
        }
    }
    void jumpPhysic(){
        if(isJumping){
            pos.y += jumpSpeed0;
            jumpSpeed0 += gravity;
        }
        if(pos.y>=510){
            isJumping = false;
            pos.y=510;
            jumpSpeed0 = 0;
        }
    }
    void UpdateRunFrame() {
        Uint32 currentTime = SDL_GetTicks();
        if(isMovingLeft||isMovingRight){
            if (currentTime > lastFrameUpdate + animationDelay) {
                FrameIndex = (FrameIndex + 1) % FrameCount;
                currentFrame.x = FrameIndex * currentFrame.w;
                lastFrameUpdate = currentTime;
            }
        }
    }
    void UpdateAttackFrame(){
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime > lastFrameUpdate + 16) {
            FrameIndex = (FrameIndex  + 1) % FrameCount;
            currentFrame.x = FrameIndex * currentFrame.w;
            lastFrameUpdate = currentTime;
            count++;
        }
        if(count == 7)
        {
            isAttacking = false;
            count = 0;
        }    
    }
};
struct entity
{
    vector2d pos;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
    entity(vector2d POS,SDL_Texture *Tex){
        pos = POS;
        tex = Tex;
        currentFrame.x = 0;
        currentFrame.y = 0;
        currentFrame.w = 581;
        currentFrame.h = 110;
    };
};
struct Graphic{
    SDL_Window* window;
    SDL_Renderer* render;
    void logErrorAndExit(const char* msg, const char* error);
};