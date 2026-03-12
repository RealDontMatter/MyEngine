#include <engine/components/Transform.hpp>
#include <engine/Vector3.hpp>


void engine::components::Transform::setPosition(const Vector3 &position) { this->position_ = position; }
void engine::components::Transform::setRotation(const Vector3 &rotation) { this->rotation_ = rotation; }
void engine::components::Transform::setScale(const Vector3 &scale) { this->scale_ = scale; }

const engine::Vector3 & engine::components::Transform::getPosition() const { return this->position_; }
const engine::Vector3 & engine::components::Transform::getRotation() const { return this->rotation_; }
const engine::Vector3 & engine::components::Transform::getScale() const { return this->scale_; }

void engine::components::Transform::set_data(const Vector3 position, const Vector3 rotation, const Vector3 scale) {
    this->position_ = position;
    this->rotation_ = rotation;
    this->scale_ = scale;
}
