#include "vec3.h"

ostream& operator<<(ostream& out, const Vec3& v)
{
	out << "(" << v.x << "," << v.y << "," << v.z << ")";
	return out;
}

double Vec3::module2() const {
	return this->x*this->x + this->y*this->y + this->z*this->z;
}

double Vec3::module() const {
	return sqrt(this->module2());
}

Vec3 Vec3::operator+(const Vec3& other) const {
	return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
	return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vec3 Vec3::operator-() const {
	return Vec3(-this->x, -this->y, -this->z);
}

Vec3 Vec3::operator*(double scalar) const {
	return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
}

Vec3 operator*(double scalar, const Vec3 & vector) {
	return Vec3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

double Vec3::operator*(const Vec3 & other) const {
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
	double divisor = sqrt(this->operator*(*this) * (v * v));
	double cosine = this->operator*(v) / divisor;
	double sine = this->cross(v).module() / divisor;

	return atan2(sine, cosine);
}