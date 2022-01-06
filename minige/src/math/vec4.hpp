#pragma once
#include "so.h"
#include <iostream>

/* todo: template for float and double type */

namespace gengine {
    namespace math {
        struct SO_API vec4 {
            float x, y, z, w;
            vec4() = default;
            inline vec4(const float& x, const float& y, const float& z, const float& w) : x(x), y(y), z(z), w(w)
            {
            }

            float operator[](const int index) const;

            float dot(const vec4& vector) const;

            SO_API friend vec4 operator+(const vec4& left, const vec4& right);
            SO_API friend vec4 operator-(const vec4& left, const vec4& right);
            SO_API friend vec4 operator-(const vec4& operand);
            SO_API friend vec4 operator*(const vec4& vector, float scalar);
            SO_API friend vec4 operator*(float scalar, const vec4& vector);
            SO_API friend vec4 operator*(const vec4& left, const vec4& right);
            SO_API friend vec4 operator/(const vec4& left, const vec4& right);
            SO_API friend bool operator==(const vec4& left, const vec4& right);
            SO_API friend std::ostream& operator<<(std::ostream& out, const vec4& vector);

            static const vec4 ZERO;
        };
    }
}