#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

#define BRICK_ROWS 5
#define BRICK_COLS 10

typedef struct {
    float x, y, width, height, speed;
} Paddle;

typedef struct {
    float x, y, size, dx, dy;
} Ball;

typedef struct {
    float x, y, width, height;
    bool isDestroyed;
    int health;    
    Uint8 r, g, b;  
} Brick;

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) return -1;

    SDL_Window* window = SDL_CreateWindow("Breakout - YZM104", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) return -1;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return -1;

    int lives = 3;
    
    Paddle paddle = { .width = 100, .height = 15, .x = (WINDOW_WIDTH / 2.0f) - 50, .y = WINDOW_HEIGHT - 40, .speed = 8.0f };
    Ball ball = { .size = 15, .x = (WINDOW_WIDTH / 2.0f) - 7.5f, .y = WINDOW_HEIGHT / 2.0f, .dx = 4.0f, .dy = -4.0f };
    Brick bricks[BRICK_ROWS][BRICK_COLS];

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            bricks[i][j].width = 65;
            bricks[i][j].height = 25;
            bricks[i][j].x = j * (65 + 10) + 30; 
            bricks[i][j].y = i * (25 + 10) + 50; 
            bricks[i][j].isDestroyed = false;
            
            if (i == 0) { 
                bricks[i][j].health = 3; bricks[i][j].r = 255; bricks[i][j].g = 50; bricks[i][j].b = 50;
            } else if (i == 1 || i == 2) {
                bricks[i][j].health = 2; bricks[i][j].r = 255; bricks[i][j].g = 150; bricks[i][j].b = 50;
            } else { 
                bricks[i][j].health = 1; bricks[i][j].r = 50; bricks[i][j].g = 255; bricks[i][j].b = 50;
            }
        }
    }

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
        }

        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT]) paddle.x -= paddle.speed;
        if (state[SDL_SCANCODE_RIGHT]) paddle.x += paddle.speed;

        if (paddle.x < 0) paddle.x = 0;
        if (paddle.x + paddle.width > WINDOW_WIDTH) paddle.x = WINDOW_WIDTH - paddle.width;

        ball.x += ball.dx;
        ball.y += ball.dy;

        if (ball.x <= 0 || ball.x + ball.size >= WINDOW_WIDTH) ball.dx = -ball.dx;
        if (ball.y <= 0) ball.dy = -ball.dy;
        
        if (ball.y + ball.size >= WINDOW_HEIGHT) {
            lives--;
            if (lives <= 0) {
                printf("Oyun Bitti! Kaybettin.\n");
                isRunning = false;
            } else {
                paddle.x = (WINDOW_WIDTH / 2.0f) - 50;
                ball.x = (WINDOW_WIDTH / 2.0f) - 7.5f;
                ball.y = WINDOW_HEIGHT / 2.0f;
                ball.dy = -4.0f; 
            }
        }

        if (ball.x < paddle.x + paddle.width && ball.x + ball.size > paddle.x && 
            ball.y < paddle.y + paddle.height && ball.y + ball.size > paddle.y) {
            ball.dy = -4.0f; 
            ball.y = paddle.y - ball.size; 
        }

        bool brickHit = false;
        for (int i = 0; i < BRICK_ROWS; i++) {
            for (int j = 0; j < BRICK_COLS; j++) {
                Brick* b = &bricks[i][j];
                if (!b->isDestroyed) {
                    if (ball.x < b->x + b->width && ball.x + ball.size > b->x &&
                        ball.y < b->y + b->height && ball.y + ball.size > b->y) {
                        
                        b->health--; 
                        if (b->health <= 0) {
                            b->isDestroyed = true;
                        } else if (b->health == 2) {
                            b->r = 255; b->g = 150; b->b = 50; 
                        } else if (b->health == 1) {
                            b->r = 50; b->g = 255; b->b = 50;
                        }

                        ball.dy = -ball.dy; 
                        brickHit = true;
                        break; 
                    }
                }
            }
            if (brickHit) break;
        }

        int activeBricks = 0;
        for (int i = 0; i < BRICK_ROWS; i++) {
            for (int j = 0; j < BRICK_COLS; j++) {
                if (!bricks[i][j].isDestroyed) activeBricks++;
            }
        }

        if (activeBricks == 0) {
            printf("Tebrikler! Yeni Seviyeye Geciliyor...\n");
            for (int i = 0; i < BRICK_ROWS; i++) {
                for (int j = 0; j < BRICK_COLS; j++) {
                    bricks[i][j].isDestroyed = false;
                    if (i == 0) { bricks[i][j].health = 3; bricks[i][j].r = 255; bricks[i][j].g = 50; bricks[i][j].b = 50; }
                    else if (i == 1 || i == 2) { bricks[i][j].health = 2; bricks[i][j].r = 255; bricks[i][j].g = 150; bricks[i][j].b = 50; }
                    else { bricks[i][j].health = 1; bricks[i][j].r = 50; bricks[i][j].g = 255; bricks[i][j].b = 50; }
                }
            }
            paddle.x = (WINDOW_WIDTH / 2.0f) - 50;
            ball.x = (WINDOW_WIDTH / 2.0f) - 7.5f;
            ball.y = WINDOW_HEIGHT / 2.0f;
            ball.dy = -4.0f;
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect paddleRect = {(int)paddle.x, (int)paddle.y, (int)paddle.width, (int)paddle.height};
        SDL_RenderFillRect(renderer, &paddleRect);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect ballRect = {(int)ball.x, (int)ball.y, (int)ball.size, (int)ball.size};
        SDL_RenderFillRect(renderer, &ballRect);

        for (int i = 0; i < BRICK_ROWS; i++) {
            for (int j = 0; j < BRICK_COLS; j++) {
                if (!bricks[i][j].isDestroyed) {
                    SDL_SetRenderDrawColor(renderer, bricks[i][j].r, bricks[i][j].g, bricks[i][j].b, 255);
                    SDL_Rect brickRect = {(int)bricks[i][j].x, (int)bricks[i][j].y, (int)bricks[i][j].width, (int)bricks[i][j].height};
                    SDL_RenderFillRect(renderer, &brickRect);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}