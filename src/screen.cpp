#include "screen.h"
#include <stdexcept>
#include <iostream>

Screen::Screen(): _WIDTH(720), _HEIGHT(480) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        throw std::runtime_error(std::string("Failed to initialize SDL: ") + SDL_GetError());
    }

    _window = SDL_CreateWindow("Reborn",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               _WIDTH,
                               _HEIGHT,
                               SDL_WINDOW_RESIZABLE);
    if (!_window) {
        SDL_Quit();
        throw std::runtime_error(std::string("Failed to create window: ") + SDL_GetError());
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        SDL_DestroyWindow(_window);
        SDL_Quit();
        throw std::runtime_error(std::string("Failed to create renderer: ") + SDL_GetError());
    }
}

Screen::~Screen() {
    if (_renderer) SDL_DestroyRenderer(_renderer);
    if (_window) SDL_DestroyWindow(_window);
    SDL_Quit();
}

SDL_Window* Screen::getWindow(){
    return _window;
}

SDL_Renderer* Screen::getRenderer(){
    return _renderer;
} 