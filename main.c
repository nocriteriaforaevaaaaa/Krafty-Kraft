#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>

struct DrawingStates
{
    int r;
    int b;
    int g;
    int a;
    bool isDrawing;
    SDL_Rect point;
} state;

struct Eraser
{
    bool isEraserOn;
    SDL_Rect block;
    bool isErasing;

} eraser;

// handles key down events
void keyDown(SDL_Keycode *code, struct DrawingStates *state, struct Eraser *eraser);

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 0;
    SDL_CreateWindowAndRenderer(700, 700, 0, &window, &renderer);

    SDL_SetWindowTitle(window, "Krafty Kraft");
    SDL_Surface *icon = IMG_Load("palette.png");

    SDL_SetWindowIcon(window, icon);
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

    eraser.block.h = 20;
    eraser.block.w = 20;
    eraser.isErasing = false;
    eraser.isEraserOn = false;

    state.point.h = 1;
    state.point.w = 1;

    bool quit = false;
    int mx;
    int my;
    while (!quit)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {

            case SDL_MOUSEBUTTONDOWN:
                if (eraser.isEraserOn)
                {
                    eraser.isErasing = true;
                    break;
                }
                state.isDrawing = true;
                break;

            case SDL_KEYDOWN:

                keyDown(&(event.key.keysym.sym), &state, &(eraser));

            case SDL_MOUSEBUTTONUP:
                // clear all states
                state.isDrawing = false;
                eraser.isErasing = false;
                break;

            case SDL_MOUSEMOTION:

                SDL_GetMouseState(&mx, &my);
                if (state.isDrawing)
                {
                    SDL_SetRenderDrawColor(renderer, state.r, state.g, state.b, state.a);
                    state.point.x = mx;
                    state.point.y = my;
                    SDL_RenderFillRect(renderer, &(state.point));
                    // draw a point on that location
                }
                else if (eraser.isErasing && eraser.isEraserOn)
                {
                    // draws a block of defined dimentions
                    eraser.block.x = mx - eraser.block.h / 2;
                    eraser.block.y = my - eraser.block.w / 2;
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, state.a);
                    SDL_RenderFillRect(renderer, &(eraser.block));
                }

                break;
            case SDL_QUIT:
                quit = true;
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    // destroy window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void keyDown(SDL_Keycode *code, struct DrawingStates *state, struct Eraser *eraser)
{
    switch (*code)
    {
    // keys to switch between different helpers
    case SDLK_e:
        eraser->isEraserOn = true;
        break;

    case SDLK_1:
        if (eraser->isEraserOn)
        {
            eraser->block.h = 25;
            eraser->block.w = 25;
        }
        else
        {
            state->point.w = 1;
            state->point.h = 1;
        }
        break;
        break;

    case SDLK_2:
        if (eraser->isEraserOn)
        {
            eraser->block.h = 30;
            eraser->block.w = 30;
        }
        else
        {
            state->point.w = 2;
            state->point.h = 2;
        }
        break;

    case SDLK_3:
        if (eraser->isEraserOn)
        {
            eraser->block.h = 35;
            eraser->block.w = 35;
        }
        else
        {
            state->point.w = 3;
            state->point.h = 3;
        }
        break;

    case SDLK_4:
        if (eraser->isEraserOn)
        {
            eraser->block.h = 40;
            eraser->block.w = 40;
        }
        else
        {
            state->point.w = 4;
            state->point.h = 4;
        }
        break;

    case SDLK_5:
        if (eraser->isEraserOn)
        {
            eraser->block.h = 50;
            eraser->block.w = 50;
        }
        else
        {
            state->point.w = 5;
            state->point.h = 5;
        }
        break;
    case SDLK_r:
        state->a = 255;
        state->b = 0;
        state->g = 0;
        state->r = 255;
        break;

    case SDLK_w:
        state->a = 255;
        state->b = 255;
        state->g = 255;
        state->r = 255;
        break;
    case SDLK_b:
        state->r = 0;
        state->b = 255;
        state->g = 0;
        state->a = 255;
        break;

    case SDLK_g:
        state->r = 0;
        state->b = 0;
        state->g = 255;
        state->a = 255;
        break;

    case SDLK_p:
        eraser->isEraserOn = false;
        break;
    }
}
