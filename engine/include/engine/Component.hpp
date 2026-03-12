#pragma once
#include <concepts>


namespace engine::components {
    class Transform;
}

namespace engine {
    class GameObject;
    class Component {
        bool has_started_ = false;
        GameObject* _game_object;
    public:
        virtual ~Component() = default;
        Component();

        [[nodiscard]] GameObject* get_owner() const;
        void set_owner(GameObject *game_object);

        [[nodiscard]] components::Transform* get_transform();
        template<std::derived_from<Component> T>
        [[nodiscard]] T* get_component();

        virtual void awake() {}
        virtual void start() {}
        virtual void update() {}

        void set_has_started(bool has_started = true);
        [[nodiscard]] bool has_started() const;
    };
}

#include <engine/GameObject.hpp>

template<std::derived_from<engine::Component> T>
[[nodiscard]] T* engine::Component::get_component() {
    return _game_object ? _game_object->GetComponent<T>() : nullptr;
}
