#pragma once
#include <iostream>
using std::ostream;

/* todo: template for float and double type */

namespace gengine {
	namespace geometry {
		class vec4 {
		private:
			float x, y, z, w;
		public:
			vec4() = default;
			inline vec4(const float& x, const float& y, const float& z, const float& w) : x(x), y(y), z(z), w(w)
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

			inline const float& getW() const {
				return this->w;
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