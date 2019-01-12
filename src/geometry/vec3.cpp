#include "vec3.h"

namespace gengine {
	namespace geometry {
		Vec3 operator+(const Vec3 & left, const Vec3 & right)
		{
			return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
		}

		Vec3 operator-(const Vec3 & left, const Vec3 & right)
		{
			return Vec3(left.x - right.x, left.y - right.y, left.z + right.z);
		}

		Vec3 operator-(const Vec3 & operand)
		{
			return Vec3(-operand.x, -operand.y, -operand.z);
		}

		Vec3 operator*(const Vec3 & vector, float scalar)
		{
			return Vec3(scalar*vector.x, scalar*vector.y, scalar*vector.z);
		}

		Vec3 operator*(float scalar, const Vec3 & vector)
		{
			return Vec3(scalar*vector.x, scalar*vector.y, scalar*vector.z);
		}

		Vec3 operator*(const Vec3 & left, const Vec3 & right)
		{
			return Vec3(left.x * right.x, left.y * right.y, left.z * right.z);
		}

		Vec3 operator/(const Vec3 & left, const Vec3 & right)
		{
			return Vec3(left.x / right.x, left.y / right.y, left.z / right.z);
		}

		bool operator==(const Vec3 & left, const Vec3 & right)
		{
			return left.x == right.x && left.y == right.y && left.z == right.z;
		}

		ostream& operator<<(ostream& out, const Vec3& v)
		{
			out << "vec3: (" << v.x << "," << v.y << "," << v.z << ")";
			return out;
		}

		double Vec3::module2() const {
			return this->dot(*this);
		}

		double Vec3::module() const {
			return sqrt(this->module2());
		}

		double Vec3::dot(const Vec3 & other) const {
			return this->x * other.x + this->y * other.y + this->z * other.z;
		}

		Vec3 Vec3::normalize() const {
			double length = this->module();
			return Vec3(
				this->x / length,
				this->y / length,
				this->z / length
			);
		}

		Vec3 Vec3::cross(const Vec3 & other) const {
			return Vec3(
				this->y * other.z - this->z * other.y,
				-(this->x * other.z - this->z * other.x),
				this->x*other.y - this->y*other.x
			);
		}

		double Vec3::includedAngle(Vec3 & v) const {
			// compute |u| * |v|
			double divisor = sqrt(this->module2() * v.module2());
			double cosine = this->dot(v) / divisor;
			double sine = this->cross(v).module() / divisor;

			return atan2(sine, cosine);
		}
	}
}