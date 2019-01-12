#pragma once
#include <iostream>
using std::ostream;

/* todo: template for float and double type */

namespace gengine {
	namespace geometry {
		class Vec4 {
		private:
			float x, y, z, w;
		public:
			inline Vec4(const float& x, const float& y, const float& z, const float& w) : x(x), y(y), z(z), w(w)
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

			friend Vec4 operator+(const Vec4& left, const Vec4& right);
			friend Vec4 operator-(const Vec4& left, const Vec4& right);
			friend Vec4 operator-(const Vec4& operand);
			friend Vec4 operator*(const Vec4& vector, float scalar);
			friend Vec4 operator*(float scalar, const Vec4& vector);
			friend Vec4 operator*(const Vec4& left, const Vec4& right);
			friend Vec4 operator/(const Vec4& left, const Vec4& right);
			friend bool operator==(const Vec4& left, const Vec4& right);
			friend ostream& operator<<(ostream& out, const Vec4& vector);
		};
	}
}