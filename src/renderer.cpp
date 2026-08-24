#include <renderer.h>

void Renderer::putPixel(uint32_t* framebuffer, int x, int y, int color) {
    if (x > width || y > height) return;
    framebuffer[y * (pitch / sizeof(uint32_t)) + x] = color;
}