#ifndef TriangleMesh_H
#define TriangleMesh_H

#include <iostream>
#include <vector>
#include "vec3.h"

class Triangle {
public:
	unsigned int a;
	unsigned int b;
	unsigned int c;

	inline Triangle(unsigned int a, unsigned int b, unsigned int c) :a(a), b(b), c(c) {
	}
};

class TriangleMesh {
public:
	std::vector<Vec3> vertices;
	std::vector<Triangle> faces;

	void importFromOff(std::istream &is);
	void saveAsOff(std::ostream & os);

	Vec3 surfaceNormal(Triangle & t) const;
	double facetArea(Triangle & f) const;
};

std::ostream& operator << (std::ostream & os, const Triangle& t);
std::ostream& operator << (std::ostream & os, const TriangleMesh& mesh);
#endif