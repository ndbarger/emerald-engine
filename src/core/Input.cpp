#include "emerald/core/Input.hpp"

#include <SDL.h>

namespace emerald
{
    bool Input::up = false;
    bool Input::down = false;
    bool Input::left = false;
    bool Input::right = false;
    bool Input::quit = false;

    int Input::horizontal = 0;
    int Input::vertical = 0;

    void Input::update()
    {
        // poll input/events
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_UP)
                    up = true;
                if (event.key.keysym.sym == SDLK_DOWN)
                    down = true;
                if (event.key.keysym.sym == SDLK_LEFT)
                    left = true;
                if (event.key.keysym.sym == SDLK_RIGHT)
                    right = true;
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_UP)
                    up = false;
                if (event.key.keysym.sym == SDLK_DOWN)
                    down = false;
                if (event.key.keysym.sym == SDLK_LEFT)
                    left = false;
                if (event.key.keysym.sym == SDLK_RIGHT)
                    right = false;
                break;

            default:
                break;
            }
        }

        horizontal = static_cast<int>(right) - static_cast<int>(left);
        vertical = static_cast<int>(down) - static_cast<int>(up);
    }

    bool Input::isDown(InputType type)
    {
        switch (type)
        {
        case InputType::UP:
            return up;
        case InputType::DOWN:
            return down;
        case InputType::LEFT:
            return left;
        case InputType::RIGHT:
            return right;
        case InputType::QUIT:
            return quit;
        default:
            return false;
        }
    }

    bool Input::isQuit()
    {
        return quit;
    }

    int Input::getHorizontal()
    {
        return horizontal;
    }

    int Input::getVertical()
    {
        return vertical;
    }
}