#include "vec2.hpp"

using std::ostream;

namespace gengine {
	namespace math {
		vec2 operator+(const vec2 & left, const vec2 & right)
		{
			return vec2(left.x + right.x, left.y + right.y);
		}

		vec2 operator-(const vec2 & left, const vec2 & right)
		{
			return vec2(left.x - right.x, left.y - right.y);
		}

		vec2 operator-(const vec2 & operand)
		{
			return vec2(-operand.x, -operand.y);
		}

		vec2 operator*(const vec2 & vector, float scalar)
		{
			return vec2(scalar*vector.x, scalar*vector.y);
		}

		vec2 operator*(float scalar, const vec2 & vector)
		{
			return vec2(scalar*vector.x, scalar*vector.y);
		}

		vec2 operator*(const vec2 & left, const vec2 & right)
		{
			return vec2(left.x * right.x, left.y * right.y);
		}

		vec2 operator/(const vec2 & left, const vec2 & right)
		{
			return vec2(left.x / right.x, left.y / right.y);
		}

		bool operator==(const vec2 & left, const vec2 & right)
		{
			return left.x == right.x && left.y == right.y;
		}

		ostream & operator<<(ostream & out, const vec2 & vector)
		{
			out << "vec2: (" << vector.x << ", " << vector.y << ")";
			return out;
		}

        const vec2 vec2::ZERO = vec2(0, 0);
	}
}