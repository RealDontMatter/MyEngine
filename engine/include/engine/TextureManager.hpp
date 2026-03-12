#pragma once
#include <string>

#include <SFML/Graphics.hpp>

namespace engine {
    class TextureManager {
    public:
        static sf::Texture* getTexture(const std::string& filename);
    };
}
