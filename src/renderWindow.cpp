#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Entity.hpp"
#include "RenderWindow.hpp"
#include "Math.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) 
    : window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    
    if (window == NULL) {
        std::cout << "Window failed to initialize: " << SDL_GetError() << std::endl;
    }
    // creates the renderer and VSYNC syncs it with the screen refresh rate
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}


SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){

    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);
    if (texture == NULL)
        std::cout << "failed to load the texture because: " << SDL_GetError() << std::endl; 

    return texture;
}

int RenderWindow::getRefreshRate(){
    int displayIndex = SDL_GetWindowDisplayIndex( window );

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}


void RenderWindow::cleanUp(){
    SDL_DestroyWindow(window);
}


void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity){

    // represents the actual size of the texture/image
    SDL_Rect src;
    // what position do you want to start at in the texture
    src.x = p_entity.getCurrentFrame().x;
    src.y =  p_entity.getCurrentFrame().y;

    // how much from the position do you want to crop into for this sprite
    src.w =  p_entity.getCurrentFrame().w;
    src.h =  p_entity.getCurrentFrame().h;


    SDL_Rect dst;
    dst.x = p_entity.getPos().x; //* p_entity.getSpriteScale();
    dst.y = p_entity.getPos().y; // * p_entity.getSpriteScale();
    dst.w = p_entity.getCurrentFrame().w * p_entity.getSpriteScale();
    dst.h = p_entity.getCurrentFrame().h * p_entity.getSpriteScale();

    // (renderer, texture file, source of texture, texture transformation)
    SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}


void RenderWindow::display(){
    SDL_RenderPresent(renderer);
    
}