#include <renderer.h>

void Framebuffer::putPixel(int x, int y, int color) {
    if (x > width || y > height) return;
    pixels[(height - y) * (pitch / sizeof(uint32_t)) + x] = color;
}