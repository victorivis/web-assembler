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

class minhaClasse{
    private:
        int numero;
    public:
        void mostrar(){
            std::cout << "O numero: " << numero;
        }
        minhaClasse();
        ~minhaClasse();
};

minhaClasse::minhaClasse(){
    numero = 42;
    std::cout << "Classe iniciada";
}

minhaClasse::~minhaClasse(){
}

minhaClasse exibirNaTela;


void loopPrincipal(void * arg){
    Context * context = static_cast<Context*>(arg);
    static int speed = 10;

    while(SDL_PollEvent(&context->event)){
        if( context->event.type == SDL_QUIT ){
            exit(0);
        }
        else if( context->event.type == SDL_MOUSEBUTTONDOWN ){
            context->rect2.x -= 20;
        }
        else if(context->event.type == SDL_KEYDOWN){
            switch(context->event.key.keysym.sym){
                case SDLK_ESCAPE: emscripten_force_exit(0); break;
                case SDLK_UP: context->rect2.y-=speed; break;
                case SDLK_DOWN: context->rect2.y+=speed; break;
                case SDLK_RIGHT: context->rect2.x+=speed; break;
                case SDLK_LEFT: context->rect2.x-=speed; break;
                default:
                    std::cout << "testando\n";
                    exibirNaTela.mostrar();
            }
        }
    }

    SDL_RenderClear(context->renderer);
    SDL_RenderCopy(context->renderer, context->logo, NULL, &context->rect);

    SDL_SetRenderDrawColor(context->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(context->renderer, &context->rect2);
    SDL_SetRenderDrawColor(context->renderer, 9, 20, 33, 255);    
    SDL_RenderPresent(context->renderer);
}

int main(int argc, char** argv) {
    Context context;
    SDL_Init(SDL_INIT_EVERYTHING);

    context.title = "Snake";
    context.width = 1280;
    context.height = 720;

    exibirNaTela = minhaClasse();

    SDL_Window* window = SDL_CreateWindow(
        context.title.c_str(),
        50, 30,
        context.width, context.height,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    context.renderer = renderer;


    SDL_Surface * surface = SDL_LoadBMP("./assets/sdl.bmp");
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

    std::cout << "Inicio\n";
    
    emscripten_set_main_loop_arg(loopPrincipal, &context, -1, 1);

    std::cout << "Fim\n";
    SDL_DestroyTexture(context.logo);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}