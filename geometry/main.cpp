#include "vec3.h"
#include "mesh.h"
#include <fstream>

int main() {
	auto v = Vec3(1.0, 2.0, 3.0);
	std::cout << v << std::endl;

	auto a = Vec3(1.0, 2.0, 3.0);
	auto b = Vec3(1.0, 3.0, 5.0);
	std::cout << a << "+" << b << "=" << a + b << std::endl;
	std::cout << a << "-" << b << "=" << a - b << std::endl;

	std::cout << "The module of " << a << " is " << a.module() << std::endl;

	std::cout << a << " per 3 is " << a * 3 << std::endl;
	std::cout << "3 per " << a << " is " << 3 * a << std::endl;

	std::cout << "The opposite of " << v << " is " << -v << std::endl;

	std::cout << "The unit vector of " << a << " is " << a.normalize() << std::endl;

	std::cout << "The dot product of " << a << " with " << b << " is " << a * b << std::endl;

	std::cout << "The cross product of " << a << " with " << b << " is " << a.cross(b) << std::endl;
	std::cout << "The cross product of " << b << " with " << a << " is " << b.cross(a) << std::endl;

	std::cout << "The angle between " << a << " and " << b << " is " << a.includedAngle(b) << std::endl;

	TriangleMesh mesh;
	std::ifstream off_in("16Triangles.off");
	std::cout << "Reading file 16Triangles.off" << std::endl;
	mesh.importFromOff(off_in);
	std::cout << "The mesh was restored" << std::endl << mesh;

	std::ofstream off_out("16Triangles_out.off");
	std::cout << "Saving as the .off format" << std::endl;
	mesh.saveAsOff(off_out);

	std::cout << "The surface' area of " << mesh.faces[0] << " is " << mesh.facetArea(mesh.faces[0]) << std::endl;
	
	std::cout << "The surface normal associated with " << mesh.faces[0] << " is " << mesh.surfaceNormal(mesh.faces[0]) << std::endl;
	std::cout << "The vertex normal associated with vectex 0 " << mesh.vertices[0] << " is " << mesh.vertexNormal(0) << std::endl;
}