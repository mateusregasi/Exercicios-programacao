#include <iostream>
#include <SDL2/SDL.h>

int WIDTH = 600;
int HEIGHT = 600;

int main(){
    int runing = true;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    window = SDL_CreateWindow("Jogo", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;

    while(runing){

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                runing = false;
        }

        SDL_RenderClear(renderer);
        // Pinta a janela
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}