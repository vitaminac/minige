#pragma once
#include "vec3.h"
#include "maths.h"

namespace gengine {
	namespace geometry {
		class Mat4 {
		private:
			float elements[4 * 4];
			inline Mat4() {
			}
		public:
			friend Mat4 operator*(const Mat4& left, const Mat4& right);

			static Mat4 diagonal(float diagonal);

			static Mat4 identity();

			static Mat4 zero();

			static Mat4 translation(const Vec3& translation);

			static Mat4 rotation(const Vec3& axis, const float angle);

			static Mat4 scale(const Vec3& k);

			static Mat4 orthographic(const Vec3& min_corner, const Vec3& max_corner);

			static Mat4 perspective(float fov, float aspectRatio, float near, float far);
		};
	}
}