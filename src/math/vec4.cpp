#include "vec4.hpp"

namespace gengine {
    namespace math {
        vec4 operator+(const vec4& left, const vec4& right)
        {
            return vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
        }

        vec4 operator-(const vec4& left, const vec4& right)
        {
            return vec4(left.x - right.x, left.y - right.y, left.z + right.z, left.w + right.w);
        }

        vec4 operator-(const vec4& operand)
        {
            return vec4(-operand.x, -operand.y, -operand.z, -operand.w);
        }

        vec4 operator*(const vec4& vector, float scalar)
        {
            return vec4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w);
        }

        vec4 operator*(float scalar, const vec4& vector)
        {
            return vec4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w);
        }

        vec4 operator*(const vec4& left, const vec4& right)
        {
            return vec4(left.x * right.x, left.y * right.y, left.z * right.z, left.w / right.w);
        }

        vec4 operator/(const vec4& left, const vec4& right)
        {
            return vec4(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
        }

        bool operator==(const vec4& left, const vec4& right)
        {
            return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
        }

        ostream& operator<<(ostream& out, const vec4& v)
        {
            out << "vec4: (" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
            return out;
        }
        float vec4::operator[](const int index) const
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
        float vec4::dot(const vec4& vector) const
        {
            return	(this->x * vector.x) + (this->y * vector.y) + (this->z * vector.z) + (this->w * vector.w);
        }

        const vec4 vec4::ZERO = vec4(0, 0, 0, 0);
    }
}