#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include <cmath>
#include <renderer.h>

void cleanup(SDL_Window* window);
void drawLine(Framebuffer fb, int ax, int ay, int bx, int by, int color);

int main(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to Initialize SDL3", nullptr);
        SDL_Quit();
        return 1;
    }

    int width = 800;
    int height = 600;
    SDL_Window *window = SDL_CreateWindow("SDL3 Demo", width, height, 0);

    if (!window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to Create Window", nullptr);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    if (!surface) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to Get Window Surface", nullptr);
        cleanup(window);
        return 1;
    }

    uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);
    Framebuffer framebuffer(pixels, width, height, surface->pitch);

    int ax = 7, ay = 3;
    int bx = 400, by = 300;
    int cx = 600, cy = 53;

    framebuffer.putPixel(ax, ay, SR_WHITE);
    framebuffer.putPixel(bx, by, SR_WHITE);
    framebuffer.putPixel(cx, cy, SR_WHITE);

    drawLine(framebuffer, ax, ay, bx, by, SR_RED);
    drawLine(framebuffer, bx, by, cx, cy, SR_GREEN);
    drawLine(framebuffer, cx, cy, ax, ay, SR_BLUE);

    bool running = true;
    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        if (SDL_LockSurface(surface)) {
            SDL_UnlockSurface(surface);
        }

        SDL_UpdateWindowSurface(window);
    }

    cleanup(window);

    return 0;
}

void cleanup(SDL_Window* window) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void drawLine(Framebuffer fb, int ax, int ay, int bx, int by, int color) {
    for (float t = 0; t < 1; t += 0.001) {
        int x = ax + t * (bx - ax);
        int y = ay + t * (by - ay);
        fb.putPixel(x, y, color);
    }
}