#include "game.h"
#ifdef __EMSCRIPTEN__ 
#include <emscripten/emscripten.h>
#endif
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]){
  Game jogo;

  jogo.helloWorld();
  
  #ifndef __EMSCRIPTEN__ 
    while(jogo.isRunning()){
      jogo.loopPrincipal();
    }
  #else
    emscripten_set_main_loop(jogo.loopPrincipal, 0, 1);
  #endif

  return 0;
}