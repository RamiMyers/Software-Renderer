#include <iostream>
#include <cstdint>

#define SR_WHITE 0xFFFFFFFF
#define SR_RED   0xFF0000FF
#define SR_GREEN 0x00FF00FF
#define SR_BLUE  0x0000FFFF

class Framebuffer {
    private:
        uint32_t* pixels;
        int width, height;
        int pitch;

    public:
        Framebuffer(uint32_t* pixels, int width, int height, int pitch) : width(width), height(height), pitch(pitch), pixels(pixels) {};
        void putPixel(int x, int y, int color);
        ~Framebuffer() {};
};