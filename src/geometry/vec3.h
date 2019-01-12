#pragma once
#include <iostream>
using std::ostream;

namespace gengine {
	namespace geometry {
		class Vec3 {
		private:
			float x, y, z;
		public:
			inline Vec3(const float& x, const float& y, const float& z) : x(x), y(y), z(z)
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

			friend Vec3 operator+(const Vec3& left, const Vec3& right);
			friend Vec3 operator-(const Vec3& left, const Vec3& right);
			friend Vec3 operator-(const Vec3& operand);
			friend Vec3 operator*(const Vec3& vector, float scalar);
			friend Vec3 operator*(float scalar, const Vec3& vector);
			friend Vec3 operator*(const Vec3& left, const Vec3& right);
			friend Vec3 operator/(const Vec3& left, const Vec3& right);
			friend bool operator==(const Vec3& left, const Vec3& right);
			friend ostream& operator<<(ostream& out, const Vec3& vector);

			double module2() const;
			double module() const;

			Vec3 normalize() const;

			double dot(const Vec3& other) const;
			Vec3 cross(const Vec3& other) const;

			double includedAngle(Vec3& v) const;
		};

		const Vec3 ZERO_VECTOR = Vec3(0, 0, 0);
	}
}