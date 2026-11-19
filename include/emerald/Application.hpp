#pragma once

#include <SDL2/SDL.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

namespace emerald
{
    class Application
    {
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

        bool running;
    public:
        int init();
        void run();
        void shutdown();
    };
}