#include <engine/Component.hpp>
#include <engine/GameObject.hpp>
#include <engine/components/Transform.hpp>


engine::Component::Component() : _game_object(nullptr) { }

engine::GameObject *engine::Component::get_owner() const { return _game_object; }
engine::components::Transform * engine::Component::get_transform() { return get_component<components::Transform>(); }

void engine::Component::set_owner(GameObject *game_object) {
    _game_object = game_object;
}


bool engine::Component::has_started() const {
    return has_started_;
}
void engine::Component::set_has_started(const bool has_started) {
    has_started_ = has_started;
}
