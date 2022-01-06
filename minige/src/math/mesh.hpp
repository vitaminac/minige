#pragma once
#include "so.h"
#include "vec3.hpp"
#include <vector>

namespace gengine {
	namespace math {
		class SO_API Triangle {
		public:
			unsigned int a;
			unsigned int b;
			unsigned int c;

			inline Triangle(unsigned int a, unsigned int b, unsigned int c) :a(a), b(b), c(c) {
			}
		};

		class SO_API TriangleMesh {
		public:
			// TODO: make them private
			std::vector<vec3> vertices;
			std::vector<Triangle> faces;

			void importFromOff(std::istream &is);
			void saveAsOff(std::ostream & os);

			double facetArea(Triangle & f) const;
			vec3 surfaceNormal(const Triangle & t) const;
			vec3 vertexNormal(unsigned int index) const;
		};

		SO_API std::ostream& operator<<(std::ostream& os, const Triangle& t);
		SO_API std::ostream& operator<<(std::ostream& os, const TriangleMesh& mesh);
	}
}