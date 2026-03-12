#include <iostream>
#include <map>
#include <engine/TextureManager.hpp>



sf::Texture* engine::TextureManager::getTexture(const std::string& filename) {
    static std::map<std::string, std::unique_ptr<sf::Texture>> texture_map;

    if (const auto it = texture_map.find(filename); it != texture_map.end()) {
        return it->second.get();
    }

    auto texture = std::make_unique<sf::Texture>();

    if (!texture->loadFromFile(filename)) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        throw std::runtime_error("Failed to load texture");
    }

    texture_map[filename] = std::move(texture);

    return texture_map[filename].get();
}