#include <stdio.h>
#include <./include/SDL2/SDL.h>
#include <stdbool.h>

struct drawingStates
{
    int r;
    int b;
    int g;
    int a;
    bool isDrawing;

} state;

struct Eraser
{
    bool isEraserOn;
    SDL_Rect block;
    bool isErasing;

} eraser;

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 0;
    SDL_CreateWindowAndRenderer(700, 700, 0, &window, &renderer);
    int x = 20;
    int y = 30;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Event event;

    // default configurations for scribbling
    state.r = 255;
    state.b = 255;
    state.g = 255;
    state.a = 255;
    state.isDrawing = false;

    // normal eraser dimentions;

    eraser.block.h = 50;
    eraser.block.w = 50;
    eraser.isErasing = false;
    eraser.isEraserOn = false;

    bool quit = false;
    while (!quit)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (eraser.isEraserOn)
                {
                    eraser.isErasing = true;
                    break;
                }
                state.isDrawing = true;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                // keys to switch between different helpers
                case SDLK_e:
                    eraser.isEraserOn = true;
                    break;
                case SDLK_r:
                    state.a = 255;
                    state.b = 0;
                    state.g = 0;
                    state.r = 255;
                    break;

                case SDLK_w:
                    state.a = 255;
                    state.b = 255;
                    state.g = 255;
                    state.r = 255;
                    break;
                case SDLK_b:
                    state.r = 0;
                    state.b = 255;
                    state.g = 0;
                    state.a = 255;
                    break;

                case SDLK_g:
                    state.r = 0;
                    state.b = 0;
                    state.g = 255;
                    state.a = 255;
                    break;
                }
                break;
            // not working so currently using go back to eraser on mouseUp method
            case SDLK_p:
                eraser.isEraserOn = false;
                break;

            case SDL_MOUSEBUTTONUP:
                // clear all states
                state.isDrawing = false;
                eraser.isErasing = false;
                eraser.isEraserOn = false; // hack to fix the eraser glitch
                break;

            case SDL_MOUSEMOTION:
                int mx;
                int my;

                SDL_GetMouseState(&mx, &my);
                if (state.isDrawing)
                {
                    // draw a point on that location
                    SDL_SetRenderDrawColor(renderer, state.r, state.g, state.b, state.a);
                    SDL_RenderDrawPoint(renderer, mx, my);
                }
                else if (eraser.isErasing && eraser.isEraserOn)
                {
                    // draws a block of defined dimentions
                    eraser.block.x = mx - 25;
                    eraser.block.y = my - 25;
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderFillRect(renderer, &(eraser.block));
                }

                break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    // destroy window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}