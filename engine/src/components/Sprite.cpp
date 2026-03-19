#include <engine/components/Sprite.hpp>
#include <engine/TextureManager.hpp>


void engine::components::Sprite::set_texture(const std::string &filename) {
    texture_ = TextureManager::get_texture(filename);
}

// deprecated
void engine::components::Sprite::set_texture(sf::Texture &texture) { }


const sf::Texture* engine::components::Sprite::get_texture() const {
    return texture_.get();
}

void engine::components::Sprite::set_density(const float density) {
    _density = density;
}

float engine::components::Sprite::get_density() const {
    return _density;
}


engine::components::Sprite* engine::components::Sprite::set_data(const std::string &filename, const float density) {
    texture_ = TextureManager::get_texture(filename);
    _density = density;
    return this;
}
