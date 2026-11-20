#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace emerald
{
    class Texture
    {
    private:
        SDL_Texture *texture = nullptr;

        int width = 0;
        int height = 0;

    public:
        Texture() = default;
        ~Texture();

        Texture(const Texture &) = delete;
        Texture &operator=(const Texture &) = delete;

        bool load(SDL_Renderer *renderer,
                  const std::string &path);

        void unload();

        SDL_Texture *get() const { return texture; }

        int getWidth() const { return width; }
        int getHeight() const { return height; }

        bool isLoaded() const { return texture != nullptr; }
    };
}