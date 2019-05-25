#pragma once
#include <iostream>
using std::ostream;

namespace gengine {
	namespace geometry {
		class vec2 {
		private:
			float x, y;
		public:
			inline vec2(const float& x, const float& y) : x(x), y(y)
			{
			}

			inline const float& getX()const {
				return this->x;
			}

			inline const float& getY() const {
				return this->y;
			}

			friend vec2 operator+(const vec2& left, const vec2& right);
			friend vec2 operator-(const vec2& left, const vec2& right);
			friend vec2 operator-(const vec2& operand);
			friend vec2 operator*(const vec2& vector, float scalar);
			friend vec2 operator*(float scalar, const vec2& vector);
			friend vec2 operator*(const vec2& left, const vec2& right);
			friend vec2 operator/(const vec2& left, const vec2& right);
			friend bool operator==(const vec2& left, const vec2& right);
			friend ostream& operator<<(ostream& out, const vec2& vector);
		};
	}
}