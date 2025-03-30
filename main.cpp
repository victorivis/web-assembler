#include <SDL2/SDL.h>
#include <emscripten.h>
#include <iostream>

struct Context {
  std::string title;
  int width, height;
  SDL_Renderer * renderer;
  SDL_Event event;
  SDL_Rect rect, rect2;
  SDL_Texture * logo;
};

void callback(void * arg){
  Context * context = static_cast<Context*>(arg);
    while(SDL_PollEvent(&context->event)){
      if( context->event.type == SDL_QUIT ){
        exit(0);
      }else if( context->event.type == SDL_MOUSEBUTTONDOWN ){
        context->rect2.x -= 20;
      }
    }

    SDL_RenderClear(context->renderer);
    SDL_SetRenderDrawColor(context->renderer, 255, 255, 255, 255);
    //SDL_RenderDrawRect(renderer, &rect2);
    SDL_RenderFillRect(context->renderer, &context->rect2);
    SDL_SetRenderDrawColor(context->renderer, 9, 20, 33, 255);
    SDL_RenderCopy(context->renderer, context->logo, NULL, &context->rect);
    SDL_RenderPresent(context->renderer);
}

int main(int argc, char** argv) {
  Context context;
  SDL_Init(SDL_INIT_EVERYTHING);

  context.title = "SDL2 It's Works!";
  context.width = 1280;
  context.height = 720;

  SDL_Window* window = SDL_CreateWindow(
      context.title.c_str(),
      50, 30,
      context.width, context.height,
      SDL_WINDOW_SHOWN
      );

  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
  context.renderer = renderer;


  SDL_Surface * surface = SDL_LoadBMP("./sdl.bmp");
  context.logo = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  context.rect.x = 50;
  context.rect.y = 20;
  context.rect.w = surface->w;
  context.rect.h = surface->h;

  context.rect2.x = 800;
  context.rect2.y = 20;
  context.rect2.w = 300;
  context.rect2.h = 300;

  emscripten_set_main_loop_arg(callback, &context, -1, 1);

  SDL_DestroyTexture(context.logo);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}