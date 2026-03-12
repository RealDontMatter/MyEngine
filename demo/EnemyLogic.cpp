#include "EnemyLogic.hpp"

#include "engine/Time.hpp"
#include "engine/Vector3.hpp"
#include "engine/components/Transform.hpp"

void EnemyLogic::start() {

}
void EnemyLogic::update() {
    engine::Vector3 dir = engine::Vector3::Normalize(_player->get_transform()->getPosition() - get_transform()->getPosition());
    auto transform = get_transform();
    transform->setPosition(transform->getPosition() + dir * engine::Time::GetDeltaTime() * _move_speed);
}

void EnemyLogic::set_data(engine::GameObject *player, const float move_speed) {
    _player = player;
    _move_speed = move_speed;
}
