#include "vec4.h"

namespace gengine {
	namespace geometry {
		Vec4 operator+(const Vec4& left, const Vec4& right)
		{
			return Vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
		}

		Vec4 operator-(const Vec4 & left, const Vec4 & right)
		{
			return Vec4(left.x - right.x, left.y - right.y, left.z + right.z, left.w + right.w);
		}

		Vec4 operator-(const Vec4 & operand)
		{
			return Vec4(-operand.x, -operand.y, -operand.z, -operand.w);
		}

		Vec4 operator*(const Vec4 & vector, float scalar)
		{
			return Vec4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w);
		}

		Vec4 operator*(float scalar, const Vec4 & vector)
		{
			return Vec4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w);
		}

		Vec4 operator*(const Vec4 & left, const Vec4 & right)
		{
			return Vec4(left.x * right.x, left.y * right.y, left.z * right.z, left.w / right.w);
		}

		Vec4 operator/(const Vec4 & left, const Vec4 & right)
		{
			return Vec4(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
		}

		bool operator==(const Vec4 & left, const Vec4 & right)
		{
			return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
		}

		ostream& operator<<(ostream & out, const Vec4 & v)
		{
			out << "vec4: (" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
			return out;
		}
		float Vec4::operator[](const int index) const
		{
			switch (index)
			{
			case 0: return this->x;
			case 1:return this->y;
			case 2:return this->z;
			case 3:return this->w;
			default:
				break;
			}
		}
		float Vec4::dot(const Vec4 & vector) const
		{
			return	(this->getX() * vector.getX()) + (this->getY() * vector.getY()) + (this->getZ() * vector.getZ()) + (this->getW() * vector.getW());
		}
	}
}