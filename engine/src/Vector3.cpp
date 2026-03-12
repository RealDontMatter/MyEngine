#include <cmath>
#include <iostream>
#include <ostream>

#include <engine/Vector3.hpp>

engine::Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) { }
engine::Vector3::Vector3(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) { }

float engine::Vector3::Magnitude() const { return sqrtf(x*x + y*y + z*z); }

engine::Vector3 engine::Vector3::Normalize() const {
    return Normalize(*this);
}

engine::Vector3 engine::Vector3::operator-(const Vector3 &other) const {
    return {x - other.x, y - other.y, z - other.z};
}

engine::Vector3 engine::Vector3::operator+(const Vector3 &other) const {
    return {x + other.x, y + other.y, z + other.z};
}

engine::Vector3 engine::Vector3::operator*(const float multiplier) const {
    return {x*multiplier, y*multiplier, z*multiplier};
}

engine::Vector3 engine::Vector3::operator/(float divisor) const {
    if (divisor == 0.0f) {
        std::cerr << "divisor cannot be zero." << std::endl;
        return *this;
    }
    return {x / divisor, y / divisor, z / divisor};
}

float engine::Vector3::Distance(const Vector3 &a, const Vector3 &b) {
    return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2) + powf(a.z - b.z, 2));
}
float engine::Vector3::Dot(const Vector3 &a, const Vector3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

engine::Vector3 engine::Vector3::Normalize(const Vector3 &a) {
    const float magnitude = a.Magnitude();
    if (magnitude == 0.0f) return a;
    return {a.x / magnitude, a.y / magnitude, a.z / magnitude};
}
