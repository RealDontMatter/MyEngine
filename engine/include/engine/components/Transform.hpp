#pragma once

#include <engine/Vector3.hpp>
#include <engine/Component.hpp>


namespace engine::components {

    class Transform : public BaseComponent<Transform> {
        Vector3 position_ = {0, 0, 0};
        Vector3 rotation_ = {0, 0, 0};
        Vector3 scale_ = {1, 1, 1};
    public:

        void setPosition(const Vector3& position);
        void setRotation(const Vector3& rotation);
        void setScale(const Vector3& scale);
        [[nodiscard]] const Vector3& getPosition() const;
        [[nodiscard]] const Vector3& getRotation() const;
        [[nodiscard]] const Vector3& getScale() const;

        void set_data(Vector3 position, Vector3 rotation, Vector3 scale);
    };
}
