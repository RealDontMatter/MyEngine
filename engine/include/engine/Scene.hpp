#pragma once

#include <memory>
#include <vector>

namespace engine {
    class GameObject;
    class Scene {
        std::vector<std::unique_ptr<GameObject>> objects;
        std::vector<std::unique_ptr<GameObject>> objectsToAdd;

        public:
        [[nodiscard]] std::vector<GameObject*> get_objects() const;
        GameObject* add_object(std::unique_ptr<GameObject> object);
        void init() const;
        void update();
    };
}