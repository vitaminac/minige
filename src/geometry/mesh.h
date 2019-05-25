#ifndef TriangleMesh_H
#define TriangleMesh_H

#include <iostream>
#include <vector>
#include "vec3.h"
namespace gengine {
	namespace geometry {
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
			std::vector<vec3> vertices;
			std::vector<Triangle> faces;

			void importFromOff(std::istream &is);
			void saveAsOff(std::ostream & os);

			double facetArea(Triangle & f) const;
			vec3 surfaceNormal(const Triangle & t) const;
			vec3 vertexNormal(unsigned int index) const;
		};

		std::ostream& operator << (std::ostream & os, const Triangle& t);
		std::ostream& operator << (std::ostream & os, const TriangleMesh& mesh);
	}
}
#endif