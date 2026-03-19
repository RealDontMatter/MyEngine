#pragma once
#include "engine/Component.hpp"

class EnemyLogic : public engine::Component {
    engine::GameObject* _player = nullptr;
    float _move_speed = 0.f;
    public:
    void start() override;
    void update() override;
    void set_data(engine::GameObject* player, float move_speed);
};


