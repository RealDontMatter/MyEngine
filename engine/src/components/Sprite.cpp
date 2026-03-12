#include <engine/components/Sprite.hpp>
#include <engine/TextureManager.hpp>


void engine::components::Sprite::set_texture(const std::string &filename) {
    texture_ = TextureManager::getTexture(filename);
}

void engine::components::Sprite::set_texture(sf::Texture &texture) {
    texture_ = &texture;
}


const sf::Texture & engine::components::Sprite::get_texture() const {
    return *texture_;
}

void engine::components::Sprite::set_density(const float density) {
    _density = density;
}

float engine::components::Sprite::get_density() const {
    return _density;
}


engine::components::Sprite* engine::components::Sprite::set_data(const std::string &filename, const float density) {
    texture_ = TextureManager::getTexture(filename);
    _density = density;
    return this;
}
