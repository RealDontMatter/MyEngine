#pragma once
#include <string>
#include <map>

#include <SFML/Graphics.hpp>

namespace engine {
    class TextureManager {
        std::map<std::string, std::weak_ptr<sf::Texture>> texture_map;
        explicit TextureManager() = default;
    public:
        TextureManager(const TextureManager&) = delete;
        void operator=(const TextureManager&) = delete;

        static TextureManager& get_instance();
        static std::shared_ptr<sf::Texture> get_texture(const std::string& filename);
    };
}
