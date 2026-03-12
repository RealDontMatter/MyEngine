#include <engine/Scene.hpp>

#include <engine/Component.hpp>
#include <engine/GameObject.hpp>

[[nodiscard]] std::vector<engine::GameObject*> engine::Scene::get_objects() const {
    std::vector<GameObject*> result;
    for (const auto& object : objects) {
        result.push_back(object.get());
    }
    return result;
}
void engine::Scene::add_object(std::unique_ptr<GameObject> object) {
    objects.push_back(std::move(object));
}

void engine::Scene::init() const {
    for (const auto& object : objects) {
        for (const auto cmp : object->get_all_components()) {
            cmp->awake();
        }
    }
}
void engine::Scene::update() const {
    for (const auto& object : objects) {
        object->Update();
    }
}