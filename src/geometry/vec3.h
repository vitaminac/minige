#pragma once
#include <iostream>
using std::ostream;

namespace gengine {
    namespace geometry {
        class vec3 {
        private:
            float x, y, z;
        public:
            inline vec3(const float& x, const float& y, const float& z) : x(x), y(y), z(z)
            {
            }

            inline const float& getX()const {
                return this->x;
            }

            inline const float& getY() const {
                return this->y;
            }

            inline const float& getZ() const {
                return this->z;
            }

            friend vec3 operator+(const vec3& left, const vec3& right);
            friend vec3 operator-(const vec3& left, const vec3& right);
            friend vec3 operator-(const vec3& operand);
            friend vec3 operator*(const vec3& vector, float scalar);
            friend vec3 operator*(float scalar, const vec3& vector);
            friend vec3 operator*(const vec3& left, const vec3& right);
            friend vec3 operator/(const vec3& left, const vec3& right);
            friend bool operator==(const vec3& left, const vec3& right);
            friend ostream& operator<<(ostream& out, const vec3& vector);

            double module2() const;
            double module() const;

            vec3 normalize() const;

            double dot(const vec3& other) const;
            vec3 cross(const vec3& other) const;

            double includedAngle(vec3& v) const;

            static const vec3 ZERO;
            static const vec3 RIGHT;
            static const vec3 UP;
            static const vec3 FORWARD;
        };
    }
}