#pragma once
#include "so.h"
#include <iostream>

namespace gengine {
	namespace math {
		struct SO_API vec3 {
			float x, y, z;
			inline vec3(const float& x, const float& y, const float& z) : x(x), y(y), z(z)
			{
			}

			SO_API friend vec3 operator+(const vec3& left, const vec3& right);
			SO_API friend vec3 operator-(const vec3& left, const vec3& right);
			SO_API friend vec3 operator-(const vec3& operand);
			SO_API friend vec3 operator*(const vec3& vector, float scalar);
			SO_API friend vec3 operator*(float scalar, const vec3& vector);
			SO_API friend vec3 operator*(const vec3& left, const vec3& right);
			SO_API friend vec3 operator/(const vec3& left, const vec3& right);
			SO_API friend bool operator==(const vec3& left, const vec3& right);
			SO_API friend std::ostream& operator<<(std::ostream& out, const vec3& vector);

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