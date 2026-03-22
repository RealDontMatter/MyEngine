#pragma once
#include <engine/Engine.hpp>


class PlayerMovement : public engine::BaseComponent<PlayerMovement> {
    float movement_speed_ = 1.f;

    float clock_ = 0;
    engine::Vector3 starting_position_;
public:



    void update() override;
    void start() override;

    PlayerMovement* set_data(float movement_speed);
};

