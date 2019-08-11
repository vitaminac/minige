#pragma once
#include "vec3.h"
#include "vec4.h"
#include "maths.h"

namespace gengine {
	namespace geometry {
		/* Column Major 4x4 Matrix */
		typedef struct mat4 {
			union
			{
				float elements[4 * 4];
				vec4 columns[4];
			};

			mat4() = default;

			friend mat4 operator*(const mat4& left, const mat4& right);
            friend vec3 operator*(const mat4& left, const vec3& right);
            friend vec4 operator*(const mat4& left, const vec4& right);

			const vec4& operator[](const int index) const;

			static mat4 diagonal(const float diagonal);

			static mat4 identity();

			static mat4 zero();

			static mat4 translation(const vec3& translation);

			static mat4 rotation(const vec3& axis, const float angle);

			static mat4 scale(const vec3& k);

			static mat4 orthographic(const vec3& min_corner, const vec3& max_corner);

			static mat4 perspective(float fov, float aspectRatio, float near, float far);
		} mat4;
	}
}