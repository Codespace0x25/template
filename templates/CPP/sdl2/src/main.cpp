#include <SDL2/SDL.h>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("SDL2 Template", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                        WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cout << "SDL_CreateWindow Error: "<< SDL_GetError()<<"\n";
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {
    std::cout << "SDL_CreateRenderer Error: %s" << SDL_GetError()<<"\n";
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  int running = 1;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
