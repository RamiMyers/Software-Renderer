#include <iostream>
#include <cstdint>

class Renderer {
    private:
        int width, height;
        int pitch;

    public:
        Renderer(int width, int height, int pitch) : width(width), height(height), pitch(pitch) {};
        void putPixel(uint32_t* framebuffer, int x, int y, int color);
        ~Renderer();
};