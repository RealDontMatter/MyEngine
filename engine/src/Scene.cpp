#include <algorithm>
#include <vector>
#include <memory>

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
engine::GameObject* engine::Scene::add_object(std::unique_ptr<GameObject> object) {
    objectsToAdd.push_back(std::move(object));
    return objectsToAdd.back().get();
}

void engine::Scene::init() const {
    for (const auto& object : objects) {
        for (const auto cmp : object->get_all_components()) {
            cmp->awake();
        }
    }
}
void engine::Scene::update() {
    for (int i = 0; i < objects.size(); i++) {
        auto &object = objects[i];
        object->Update();
    }

    if (!objectsToAdd.empty()) {
        objects.insert(
            objects.end(),
            std::make_move_iterator(objectsToAdd.begin()),
            std::make_move_iterator(objectsToAdd.end())
        );
        objectsToAdd.clear();
    }
}