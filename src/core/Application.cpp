#include "emerald/core/Application.hpp"
#include "emerald/core/Logger.hpp"
#include "emerald/core/Input.hpp"

#include <iostream>

namespace emerald
{
    int Application::init()
    {
        // initialize SDL
        int rendererFlags, windowFlags;

        // init all our stuff
        Logger::init("logs/emerald.log");

        Logger::info("Starting Emerald Engine...");

        rendererFlags = 0; // SDL render flags
        windowFlags = 0;   // SDL window flags

        running = false; // not running yet

        Logger::info("Initializing SDL...");

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            Logger::fatal("SDL initialization failed: {}", SDL_GetError());
            return 1;
        }

        Logger::info("SDL initialized successfully.");

        Logger::info("Creating window...");

        window = SDL_CreateWindow(
            "Emerald Engine Runtime",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

        Logger::info("Creating renderer...");

        renderer = SDL_CreateRenderer(window, -1, rendererFlags);

        if (renderer == NULL)
        {
            Logger::fatal("Failed to create renderer: {}", SDL_GetError());
            return 1;
        }

        Logger::info("Initialization complete.");

        return 0;
    }

    void Application::run()
    {
        int x, y;

        Logger::info("Starting application...");

        running = true;

        x = 0;
        y = 0;

        // init everything

        const double UPDATE_RATE = 1.0 / 60.0;

        double accumulator = 0.0;

        unsigned int previousTime = SDL_GetPerformanceCounter();
        const double frequency = static_cast<double>(SDL_GetPerformanceFrequency());

        while (running)
        {
            unsigned int currentTime = SDL_GetPerformanceCounter();

            double deltaTime = static_cast<double>(currentTime - previousTime) / frequency;

            previousTime = currentTime;

            accumulator += deltaTime;

            Input::update();

            if (Input::isQuit())
                running = false;

            while (accumulator >= UPDATE_RATE)
            {
                // update components
                // we're going to start out by hard-coding a simple top-down movement system
                x += 4 * Input::getHorizontal(); // with input: x += Input.horizontal * speed * deltaTime;
                y += 4 * Input::getVertical();   // with input: y += Input.vertical * speed * deltaTime;

                accumulator -= UPDATE_RATE;
            }

            // draw scene
            SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
            SDL_RenderClear(renderer);

            // This rectangle will initially represent a "player object"
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, new SDL_Rect({x, y, 64, 96}));

            // present scene
            SDL_RenderPresent(renderer);
        }
    }

    void Application::shutdown()
    {
        Logger::info("Shutting down Emerald Engine...");

        // clean up the memory used by SDL

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        // clean up our memory (if needed)

        // quit SDL
        SDL_Quit();

        Logger::shutdown();
    }
}