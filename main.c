#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

typedef struct {
    float x, y;
    float width, height;
} Paddle;

typedef struct {
    float x, y;
    float size; 
} Ball;

int main(int argc, char* argv[]) {

    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL baslatilamadi! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Breakout - YZM104", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Pencere olusturulamadi! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer olusturulamadi! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Paddle paddle = {
        .width = 100, 
        .height = 15,
        .x = (WINDOW_WIDTH / 2.0f) - 50,
        .y = WINDOW_HEIGHT - 40      
    };

    Ball ball = {
        .size = 15,
        .x = (WINDOW_WIDTH / 2.0f) - 7.5f,
        .y = WINDOW_HEIGHT / 2.0f
    };

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect paddleRect = {(int)paddle.x, (int)paddle.y, (int)paddle.width, (int)paddle.height};
        SDL_RenderFillRect(renderer, &paddleRect);

        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        SDL_Rect ballRect = {(int)ball.x, (int)ball.y, (int)ball.size, (int)ball.size};
        SDL_RenderFillRect(renderer, &ballRect);

        SDL_RenderPresent(renderer);
        
        SDL_Delay(16); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}