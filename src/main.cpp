#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>

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

    bool running = true;
    uint32_t* framebuffer = static_cast<uint32_t*>(surface->pixels);

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        if (SDL_LockSurface(surface)) {
            framebuffer[300 * (surface->pitch / sizeof(uint32_t)) + 400] = 0xFFFFFFFF;
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