#pragma once

#include "emerald/graphics/Texture.hpp"

#include <memory>
#include <string>
#include <unordered_map>

namespace emerald
{
    class ResourceManager
    {
    private:
        std::unordered_map<std::string, std::unique_ptr<Texture>> textures;

    public:
        ResourceManager() = default;
        ~ResourceManager() = default;

        ResourceManager(const ResourceManager &) = delete;
        ResourceManager &operator=(const ResourceManager &) = delete;

        Texture *loadTexture(SDL_Renderer *renderer, const std::string &name, const std::string &path);

        Texture *getTexture(const std::string &name);

        void unloadTexture(const std::string &name);
        void unloadAll();
    };
}