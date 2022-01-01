#include "vec3.hpp"

namespace gengine {
    namespace math {
        vec3 operator+(const vec3& left, const vec3& right)
        {
            return vec3(left.x + right.x, left.y + right.y, left.z + right.z);
        }

        vec3 operator-(const vec3 & left, const vec3 & right)
        {
            return vec3(left.x - right.x, left.y - right.y, left.z - right.z);
        }

        vec3 operator-(const vec3 & operand)
        {
            return vec3(-operand.x, -operand.y, -operand.z);
        }

        vec3 operator*(const vec3 & vector, float scalar)
        {
            return vec3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
        }

        vec3 operator*(float scalar, const vec3 & vector)
        {
            return vec3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
        }

        vec3 operator*(const vec3 & left, const vec3 & right)
        {
            return vec3(left.x * right.x, left.y * right.y, left.z * right.z);
        }

        vec3 operator/(const vec3 & left, const vec3 & right)
        {
            return vec3(left.x / right.x, left.y / right.y, left.z / right.z);
        }

        bool operator==(const vec3 & left, const vec3 & right)
        {
            return left.x == right.x && left.y == right.y && left.z == right.z;
        }

        ostream& operator<<(ostream & out, const vec3 & v)
        {
            out << "vec3: (" << v.x << "," << v.y << "," << v.z << ")";
            return out;
        }

        double vec3::module2() const {
            return this->dot(*this);
        }

        double vec3::module() const {
            return sqrt(this->module2());
        }

        double vec3::dot(const vec3 & other) const {
            return (double)this->x* other.x + (double)this->y * other.y + (double)this->z * other.z;
        }

        vec3 vec3::normalize() const {
            double length = this->module();
            return vec3(
                this->x / length,
                this->y / length,
                this->z / length
            );
        }

        vec3 vec3::cross(const vec3 & other) const {
            return vec3(
                this->y * other.z - this->z * other.y,
                -(this->x * other.z - this->z * other.x),
                this->x * other.y - this->y * other.x
            );
        }

        double vec3::includedAngle(vec3 & v) const {
            // compute |u| * |v|
            double divisor = sqrt(this->module2() * v.module2());
            double cosine = this->dot(v) / divisor;
            double sine = this->cross(v).module() / divisor;

            return atan2(sine, cosine);
        }

        const vec3 vec3::ZERO = vec3(0, 0, 0);
        const vec3 vec3::RIGHT = vec3(1, 0, 0);
        const vec3 vec3::UP = vec3(0, 1, 0);
        const vec3 vec3::FORWARD = vec3(0, 0, 1);
    }
}