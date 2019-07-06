#pragma once
#include <iostream>
using std::ostream;

/* todo: template for float and double type */

namespace gengine {
    namespace geometry {
        struct vec4 {
            float x, y, z, w;
            vec4() = default;
            inline vec4(const float& x, const float& y, const float& z, const float& w) : x(x), y(y), z(z), w(w)
            {
            }

            float operator[](const int index) const;

            float dot(const vec4& vector) const;

            friend vec4 operator+(const vec4& left, const vec4& right);
            friend vec4 operator-(const vec4& left, const vec4& right);
            friend vec4 operator-(const vec4& operand);
            friend vec4 operator*(const vec4& vector, float scalar);
            friend vec4 operator*(float scalar, const vec4& vector);
            friend vec4 operator*(const vec4& left, const vec4& right);
            friend vec4 operator/(const vec4& left, const vec4& right);
            friend bool operator==(const vec4& left, const vec4& right);
            friend ostream& operator<<(ostream& out, const vec4& vector);
        };
    }
}