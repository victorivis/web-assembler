#pragma once
#include <SDL3/SDL.h>

class Screen{
private:
  const int _WIDTH;
  const int _HEIGHT;
  SDL_Window* _window;
  SDL_Renderer* _renderer; 

public:
  Screen();
  ~Screen();

  SDL_Window* getWindow();
  SDL_Renderer* getRenderer(); 
};
