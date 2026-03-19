#include <iostream>
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

#include <engine/TextureManager.hpp>

std::unique_ptr<engine::TextureManager> engine::TextureManager::_instance;

engine::TextureManager& engine::TextureManager::get_instance() {
    if (_instance == nullptr) {
        _instance = std::unique_ptr<TextureManager>(new TextureManager());
    }
    auto *ptr = _instance.get();
    auto &ref = *ptr;
    return ref;
}

std::shared_ptr<sf::Texture> engine::TextureManager::get_texture(const std::string& filename) {
    std::shared_ptr<sf::Texture> shr_ptr;
    if (const auto it = _texture_map.find(filename); it != _texture_map.end()) {
        shr_ptr = it->second.lock();
    }

    // 1. There is a texture in map and its valid
    if (shr_ptr != nullptr) return shr_ptr;

    // 2, 3. If there is a texture in the map but its invalid or there isn't texture in map we need to load it.
    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }
    _texture_map[filename] = texture;
    return std::move(texture);
}
