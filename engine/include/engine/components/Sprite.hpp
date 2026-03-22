#pragma once
#include <string>

#include "SFML/Graphics/Texture.hpp"

#include <engine/Component.hpp>


namespace engine {
    class GameObject;
}

namespace engine::components {
    class Sprite : public BaseComponent<Sprite> {
        std::shared_ptr<sf::Texture> texture_ = nullptr;
        float _density = 100.f;
    public:
        void set_texture(const std::string& filename);
        [[nodiscard]] const sf::Texture* get_texture() const;
        void set_density(float density);
        [[nodiscard]] float get_density() const;

        Sprite* set_data(const std::string& filename, float density = 100.f);

        [[deprecated]] void set_texture(sf::Texture& texture);
    };
}