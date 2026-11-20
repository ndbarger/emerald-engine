#include <emerald/Application.hpp>

#include <iostream>

namespace emerald
{
    int Application::init()
    {
        // initialize SDL
        int rendererFlags, windowFlags;

        rendererFlags = 0; // SDL render flags
        windowFlags = 0;   // SDL window flags

        running = false; // not running yet

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "Couldn't initialize SDL: " << SDL_GetError() << std::endl; /* TODO: create a custom logger instead of directly using iostream */
            return 1;
        }

        window = SDL_CreateWindow(
            "Emerald Engine Runtime",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

        renderer = SDL_CreateRenderer(window, -1, rendererFlags);

        if (renderer == NULL)
        {
            std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
            return 1;
        }
    }

    void Application::run()
    {
        running = true;

        while (running)
        {
            // poll input/events
            SDL_Event event;

            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
                }
            }

            // update components

            // draw scene
            SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
            SDL_RenderClear(renderer);

            // present scene
            SDL_RenderPresent(renderer);
        }
    }

    void Application::shutdown()
    {
        // clean up the memory used by SDL
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        // clean up our memory (if needed)

        // quit SDL
        SDL_Quit();
    }
}