#pragma once
#include "engine/Component.hpp"

namespace engine::components {
    class PerspectiveCamera : public Component {
        float z_near_ = 0.1f, z_far_ = 100.0f, z_fov_ = 60.0f;
    public:
        void set_data(float zNear, float zFar, float zFov);
        [[nodiscard]] float get_z_near() const;
        [[nodiscard]] float get_z_far() const;
        [[nodiscard]] float get_z_fov() const;
    };
}
