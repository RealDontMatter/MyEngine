#include <iostream>
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

#include <engine/TextureManager.hpp>


engine::TextureManager * engine::TextureManager::get_instance() {
    return _instance.get();
}

std::shared_ptr<sf::Texture> engine::TextureManager::get_texture(const std::string& filename) {
    // std::map<std::string, std::weak_ptr<sf::Texture>> texture_map
    auto& textures = get_instance()->texture_map;

    std::shared_ptr<sf::Texture> shr_ptr;
    if (const auto it = textures.find(filename); it != textures.end()) {
        shr_ptr = it->second.lock();
    }

    // 1. There is a texture in map and its valid
    if (shr_ptr != nullptr) return shr_ptr;

    // 2, 3. If there is a texture in the map but its invalid or there isn't texture in map we need to load it.
    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }
    textures[filename] = texture;
    return std::move(texture);
}
