#include "screen.h"
#include <stdexcept>
#include <iostream>

Screen::Screen(): _WIDTH(720), _HEIGHT(480) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == false) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl; // Debug no console
        throw std::runtime_error(std::string("Failed to initialize SDL: ") + SDL_GetError());
    }

    _window = SDL_CreateWindow("Reborn", _WIDTH, _HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!_window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl; // Debug
        SDL_Quit();
        throw std::runtime_error(std::string("Failed to create window: ") + SDL_GetError());
    }

    _renderer = SDL_CreateRenderer(_window, NULL);
    if (!_renderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl; // Debug
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