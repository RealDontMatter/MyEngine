#pragma once
#include <string>
#include <map>

#include <SFML/Graphics.hpp>

namespace engine {
    class TextureManager {
        std::map<std::string, std::weak_ptr<sf::Texture>> _texture_map;
    public:
        std::shared_ptr<sf::Texture> get_texture(const std::string& filename);

    // Singleton implementation
    private:
        friend class TextureManagerTest;
        static std::unique_ptr<TextureManager> _instance;
        explicit TextureManager() = default;
    public:
        TextureManager(const TextureManager&) = delete;
        void operator=(const TextureManager&) = delete;
        static TextureManager& get_instance();
    };
}
