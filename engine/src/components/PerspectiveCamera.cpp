#include <engine/components/PerspectiveCamera.hpp>

void engine::components::PerspectiveCamera::set_data(const float zNear, const float zFar, const float zFov) {
    z_near_ = zNear;
    z_far_ = zFar;
    z_fov_ = zFov;
}

float engine::components::PerspectiveCamera::get_z_near() const {
    return z_near_;
}

float engine::components::PerspectiveCamera::get_z_far() const {
    return z_far_;
}

float engine::components::PerspectiveCamera::get_z_fov() const {
    return z_fov_;
}
