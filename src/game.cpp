#include "game.h"
#include <cmath>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

Game* globalGameInstance = nullptr;

Game::Game() : _running(true) {
  if(globalGameInstance==nullptr){
    globalGameInstance = this;
  }
}

Game::~Game() {
}

void Game::helloWorld() {
    printf("Ola de novo!\n");
}

void Game::loopPrincipal() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          #ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
          #endif
            globalGameInstance->_running = false;
        }
    }

    double now = SDL_GetTicks() / 1000.0;
    float red   = 0.5f + 0.5f * std::sin(now);
    float green = 0.5f + 0.5f * std::sin(now + M_PI * 2 / 3);
    float blue  = 0.5f + 0.5f * std::sin(now + M_PI * 4 / 3);
    
    SDL_SetRenderDrawColor(globalGameInstance->screen.getRenderer(),
                           static_cast<Uint8>(red * 255),
                           static_cast<Uint8>(green * 255),
                           static_cast<Uint8>(blue * 255),
                           255);
    SDL_RenderClear(globalGameInstance->screen.getRenderer());
    SDL_RenderPresent(globalGameInstance->screen.getRenderer());
}

bool Game::isRunning() {
    return _running;
}
