#include <iostream>
using std::ostream;

#ifndef VEC3
#define VEC3
class Vec3 {
public:
	double x;
	double y;
	double z;

	inline Vec3(const double x, const double y, const double z) : x(x), y(y), z(z)
	{
	}

	double module2() const;
	double module() const;

	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator-() const;

	Vec3 normalize() const;

	Vec3 operator*(double scalar) const;
	double operator*(const Vec3 & other) const;

	Vec3 cross(const Vec3 & other) const;

	double includedAngle(Vec3 & v) const;
};

ostream& operator<<(ostream& out, const Vec3& v);
Vec3 operator*(double scalar, const Vec3 & vector);
const Vec3 ZERO_VECTOR = Vec3(0, 0, 0);
#endif