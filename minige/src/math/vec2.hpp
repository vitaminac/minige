#pragma once
#include "so.h"
#include <iostream>

namespace gengine {
    namespace math {
        struct SO_API vec2 {
            float x, y;
            inline vec2(const float& x, const float& y) : x(x), y(y)
            {
            }

            friend vec2 operator+(const vec2& left, const vec2& right);
            friend vec2 operator-(const vec2& left, const vec2& right);
            friend vec2 operator-(const vec2& operand);
            friend vec2 operator*(const vec2& vector, float scalar);
            friend vec2 operator*(float scalar, const vec2& vector);
            friend vec2 operator*(const vec2& left, const vec2& right);
            friend vec2 operator/(const vec2& left, const vec2& right);
            friend bool operator==(const vec2& left, const vec2& right);
            friend std::ostream& operator<<(std::ostream& out, const vec2& vector);

            static const vec2 ZERO;
        };
    }
}