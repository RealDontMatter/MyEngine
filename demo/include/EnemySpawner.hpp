#pragma once
#include <engine/Component.hpp>

class EnemySpawner : public engine::BaseComponent<EnemySpawner> {
    float _spawning_interval = 10000.f;
    float _timer = 0.f;
    engine::GameObject* _prefab = nullptr;
public:
    void start() override;
    void update() override;
    void set_data(float spawning_interval, engine::GameObject* prefab);
};


