#pragma once
#include <memory>
#include <string>
#include <vector>

#include "SFML/Graphics/Transform.hpp"

namespace engine::components {
    class Transform;
}

namespace engine {
    class Component;
    class GameObject {
        std::vector<std::unique_ptr<GameObject>> _children;
        std::vector<std::unique_ptr<Component>> _components;
        std::string _name, _tag;
        GameObject* _parent = nullptr;
        explicit GameObject(std::string name, std::string tag = "");
    public:
        static std::unique_ptr<GameObject> Create(std::string name, std::string tag = "");

        GameObject(const GameObject&) = delete;
        GameObject& operator=(const GameObject&) = delete;

        [[nodiscard]] const std::string& getTag() const;
        [[nodiscard]] const std::string& getName() const;
        void setName(std::string name);
        void setTag(std::string tag);

        [[nodiscard]] GameObject* getParent() const;
        [[nodiscard]] std::vector<GameObject*> getChildren() const;
        void addChild(std::unique_ptr<GameObject> child);
        std::unique_ptr<GameObject> remove_child(GameObject* childPtr);
        bool has_child(GameObject* childPtr) const;
        static void Transfer(GameObject* child, GameObject* oldParent, GameObject* newParent);

        template <std::derived_from<Component> T>
        [[nodiscard]] T *GetComponent() {
            for (auto & comp : _components) {
                if (T* castedPtr = dynamic_cast<T*>(comp.get())) return castedPtr;
            }
            return nullptr;
        }
        [[nodiscard]] std::vector<Component*> get_all_components() const;
        [[nodiscard]] components::Transform* get_transform();
        template <std::derived_from<Component> T>
        T* add_component() {
            auto comp = std::make_unique<T>();
            T* ptr = comp.get();
            ptr->set_owner(this);
            _components.push_back(std::move(comp));
            return ptr;
        }

        void Update() const;
    };

}
