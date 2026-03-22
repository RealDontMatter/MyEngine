#include "EnemySpawner.hpp"

#include <iostream>


#include "engine/Time.hpp"
#include "engine/Vector3.hpp"
#include "engine/components/Transform.hpp"
#include "SFML/System/Time.hpp"

void EnemySpawner::start() {

}
void EnemySpawner::update() {
    static int count = 0;
    _timer += engine::Time::GetDeltaTime();

    if (_timer > _spawning_interval) {
        _timer -= _spawning_interval;
        if (count < 3) {
            count++;
            Instantiate(_prefab);
            std::cout << "Created enemy" << std::endl;
        }
    }
}

void EnemySpawner::set_data(float spawning_interval, engine::GameObject* prefab) {
    _spawning_interval = spawning_interval;
    _prefab = prefab;
}
