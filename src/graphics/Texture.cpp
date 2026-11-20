#include "emerald/graphics/Texture.hpp"

#include <SDL2/SDL_image.h>

namespace emerald
{
    Texture::~Texture()
    {
        unload();
    }

    bool Texture::load(SDL_Renderer *renderer, const std::string &path)
    {
        unload();

        SDL_Surface *surface = IMG_Load(path.c_str());

        if (!surface)
            return false;

        texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (texture)
        {
            width = surface->w;
            height = surface->h;
        }

        SDL_FreeSurface(surface);

        return texture != nullptr;
    }

    void Texture::unload()
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        width = 0;
        height = 0;
    }
}