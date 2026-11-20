#include "emerald/core/ResourceManager.hpp"

namespace emerald
{
    Texture *ResourceManager::loadTexture(SDL_Renderer *renderer, const std::string &name, const std::string &path)
    {
        // check if already loaded
        auto it = textures.find(name);

        if (it != textures.end())
            return it->second.get();

        auto texture = std::make_unique<Texture>();

        if (!texture->load(renderer, path))
            return nullptr;

        Texture *result = texture.get();

        textures.emplace(name, std::move(texture));

        return result;
    }

    Texture *ResourceManager::getTexture(const std::string &name)
    {
        auto it = textures.find(name);

        if (it == textures.end())
            return nullptr;

        return it->second.get();
    }

    void ResourceManager::unloadTexture(const std::string &name)
    {
        textures.erase(name);
    }

    void ResourceManager::unloadAll()
    {
        textures.clear();
    }
}