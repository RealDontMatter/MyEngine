#pragma once

namespace engine {
    struct Vector3 {
        float x, y, z;
        Vector3();
        Vector3(float _x, float _y, float _z=0);
        [[nodiscard]] float Magnitude() const;
        [[nodiscard]] Vector3 Normalize() const;

        Vector3 operator-(const Vector3 & other) const;
        Vector3 operator+(const Vector3 & other) const;
        Vector3 operator*(float multiplier) const;
        Vector3 operator/(float divisor) const;

        static float Distance(const Vector3& a, const Vector3& b);
        static float Dot(const Vector3& a, const Vector3& b);
        static Vector3 Normalize(const Vector3& a);
    };
}
