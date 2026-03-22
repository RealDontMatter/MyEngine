#pragma once
#include <engine/Component.hpp>

namespace engine {
    class GameObject;
}

namespace engine::components {
    class Camera : public BaseComponent<Camera> {
        float size_ = 5;
    public:
        void setSize(float size);
        [[nodiscard]] float getSize() const;

        void set_data(float size);
    };
}
