#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include <renderer.h>

void cleanup(SDL_Window* window);

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
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    framebuffer.putPixel(ax, ay, SR_RED);
    framebuffer.putPixel(bx, by, SR_GREEN);
    framebuffer.putPixel(cx, cy, SR_BLUE);

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