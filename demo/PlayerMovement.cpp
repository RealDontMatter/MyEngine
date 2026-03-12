#include "PlayerMovement.hpp"
#include <cmath>

#include <engine/Engine.hpp>



void PlayerMovement::start() {
    starting_position_ = get_transform()->getPosition();

}

PlayerMovement* PlayerMovement::set_data(const float movement_speed) {
    movement_speed_ = movement_speed;
    return this;
}


void PlayerMovement::update() {

    auto transform = get_transform();
    engine::Vector3 dir = engine::Vector3::Normalize({std::sinf(clock_), 0, 0});
    transform->setPosition(transform->getPosition() + dir * engine::Time::GetDeltaTime() * movement_speed_);

    clock_ += engine::Time::GetDeltaTime();
}
