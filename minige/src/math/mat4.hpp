#pragma once
#include "vec3.hpp"
#include "vec4.hpp"

namespace gengine {
	namespace math {
		/* Column Major 4x4 Matrix */
		typedef struct mat4 {
			union
			{
				float elements[4 * 4];
				vec4 columns[4];
			};

			mat4() = default;

			SO_API friend mat4 operator*(const mat4& left, const mat4& right);
			SO_API friend vec3 operator*(const mat4& left, const vec3& right);
			SO_API friend vec4 operator*(const mat4& left, const vec4& right);

			const vec4& operator[](const int index) const;

			SO_API static mat4 diagonal(const float diagonal);

			SO_API static mat4 identity();

			SO_API static mat4 zero();

			SO_API static mat4 translation(const vec3& translation);

			SO_API static mat4 rotation(const vec3& axis, const float angle);

			SO_API static mat4 scale(const vec3& k);

			SO_API static mat4 orthographic(const float left, const float right, const float bottom, const float top, const float near, const float far);

			SO_API static mat4 perspective(const float fov, const float aspectRatio, const float near, const float far);

			SO_API static mat4 perspective_frustum(const float left, const float right, const float bottom, const float top, const float near, const float far);
		} mat4;
	}
}