#pragma once
#include <iostream>
using std::ostream;

namespace gengine {
	namespace geometry {
		class Vec2 {
		private:
			float x, y;
		public:
			inline Vec2(const float& x, const float& y) : x(x), y(y)
			{
			}

			inline const float& getX()const {
				return this->x;
			}

			inline const float& getY() const {
				return this->y;
			}

			friend Vec2 operator+(const Vec2& left, const Vec2& right);
			friend Vec2 operator-(const Vec2& left, const Vec2& right);
			friend Vec2 operator-(const Vec2& operand);
			friend Vec2 operator*(const Vec2& vector, float scalar);
			friend Vec2 operator*(float scalar, const Vec2& vector);
			friend Vec2 operator*(const Vec2& left, const Vec2& right);
			friend Vec2 operator/(const Vec2& left, const Vec2& right);
			friend bool operator==(const Vec2& left, const Vec2& right);
			friend ostream& operator<<(ostream& out, const Vec2& vector);
		};
	}
}