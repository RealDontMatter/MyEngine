#include <engine/components/Camera.hpp>




void engine::components::Camera::setSize(const float size) {
    size_ = size;
}

float engine::components::Camera::getSize() const {
    return size_;
}

void engine::components::Camera::set_data(const float size) {
    size_ = size;
}
