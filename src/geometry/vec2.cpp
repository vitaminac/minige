#include "vec2.h"

namespace gengine {
	namespace geometry {
		Vec2 operator+(const Vec2 & left, const Vec2 & right)
		{
			return Vec2(left.x + right.x, left.y + right.y);
		}

		Vec2 operator-(const Vec2 & left, const Vec2 & right)
		{
			return Vec2(left.x - right.x, left.y - right.y);
		}

		Vec2 operator-(const Vec2 & operand)
		{
			return Vec2(-operand.x, -operand.y);
		}

		Vec2 operator*(const Vec2 & vector, float scalar)
		{
			return Vec2(scalar*vector.x, scalar*vector.y);
		}

		Vec2 operator*(float scalar, const Vec2 & vector)
		{
			return Vec2(scalar*vector.x, scalar*vector.y);
		}

		Vec2 operator*(const Vec2 & left, const Vec2 & right)
		{
			return Vec2(left.x * right.x, left.y * right.y);
		}

		Vec2 operator/(const Vec2 & left, const Vec2 & right)
		{
			return Vec2(left.x / right.x, left.y / right.y);
		}

		bool operator==(const Vec2 & left, const Vec2 & right)
		{
			return left.x == right.x && left.y == right.y;
		}

		ostream & operator<<(ostream & out, const Vec2 & vector)
		{
			out << "vec2: (" << vector.x << ", " << vector.y << ")";
			return out;
		}
	}
}