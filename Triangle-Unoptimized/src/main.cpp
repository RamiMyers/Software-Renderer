#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include <cmath>
#include <utility>
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

    int ax = 200, ay = 150;
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
    float t;
    int y;
    bool steep = std::abs(ax - bx) < std::abs(ay - by);

    // Swaps x & y values of each point if it is steep; transposes image so that lines are temporarily more horizontal
    if (steep) {
        std::swap(ax, ay);
        std::swap(bx, by);
    }
    // Swaps x's if the start point is to the right of the end point
    if (ax > bx) {
        std::swap(ax, bx);
        std::swap(ay, by);
    }
    // Steps through each x value
    for (int x = ax; x < bx; x++) {
        // Calculates time value using linear interpolation
        t = (x - ax) / static_cast<float>(bx - ax);
        // Calculates y value using linear interpolation
        y = std::round(ay + t * (by - ay));
        // De-transposes of the steep flag was set, otherwise puts the pixels normally
        if (steep)
            fb.putPixel(y, x, color);
        else
            fb.putPixel(x, y, color);
    }
}