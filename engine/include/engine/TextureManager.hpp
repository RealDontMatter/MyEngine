#pragma once
#include <string>

#include <SFML/Graphics.hpp>

namespace engine {
    class TextureManager {
        static std::unique_ptr<TextureManager> _instance;
        std::map<std::string, std::weak_ptr<sf::Texture>> texture_map;
    public:
        static TextureManager* get_instance();
        static std::shared_ptr<sf::Texture> get_texture(const std::string& filename);
    };
}
