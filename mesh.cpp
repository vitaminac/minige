#include "mesh.h"
#include <string>

std::ostream& operator << (std::ostream & os, const Triangle& t) {
	os << "the Triangle a:" << t.a << ", b:" << t.b << ", c: " << t.c;
	return os;
}

std::ostream& operator << (std::ostream & os, const TriangleMesh& mesh) {
	os << "the mesh has " << mesh.vertices.size() << " vertices and " << mesh.faces.size() << " faces" << std::endl;
	for (auto &v : mesh.vertices) {
		os << v << std::endl;
	}
	for (auto &f : mesh.faces) {
		os << f << std::endl;
	}
	return os;
}

void TriangleMesh::importFromOff(std::istream &is) {
	std::string header;
	// read header
	if (!(is >> header))
		throw std::string("error loading header");

	//Check if header ends with "OFF"
	if (header.length() < 3 || header.compare(header.length() - 3, 3, "OFF"))
	{
		std::cerr << "Header: " << header << std::endl;
		throw std::string("file is not in OFF file format.");
	}

	// Read the number of vertex, faces, edges
	unsigned int nv, nf, ne;
	if (!(is >> nv >> nf >> ne)) {
		throw std::string("error loading number of vertex, faces and edges");
	}

	std::cerr << "vertex: " << nv << " faces: " << nf << " edges: " << ne << std::endl;

	this->vertices.reserve(nv);
	this->faces.reserve(nf);

	// read the values of vertex
	for (int i = 0; i < nv; i++) {
		double x, y, z;
		if (!(is >> x >> y >> z))
			throw std::string("error loading coordinates");
		this->vertices.push_back(Vec3(x, y, z));
	}

	// read the values of triangles
	for (int i = 0; i < nf; i++)
	{
		unsigned int n, a, b, c;
		//Read values for indexes
		if (!(is >> n >> a >> b >> c))
			throw std::string("error loading triangles");

		//Check it a triangle mesh
		if (n != 3)
		{
			std::cerr << "Face: " << i << std::endl;
			throw std::string("This reader only support triangle faces");
		}

		//Check some errors
		if (a < 0 || b < 0 || c < 0 || a >= nv || b >= nv || c >= nv)
		{
			std::cerr << "Triangle: " << i << " -> " << a << " " << b << " " << c << std::endl;
			throw std::string("Invalid value for index");
		}

		this->faces.push_back(Triangle(a, b, c));
	}
}

void TriangleMesh::saveAsOff(std::ostream & os) {
	// write the header
	os << "OFF" << "\n" << this->vertices.size() << " " << this->faces.size() << " " << 0 << "\n";

	// write vertices
	for (auto & v : this->vertices) {
		os << v.x << " " << v.y << " " << v.z << "\n";
	}
	// write triangles
	for (auto & t : this->faces) {
		os << "3 " << t.a << " " << t.b << " " << t.c << "\n";
	}
}

Vec3 TriangleMesh::surfaceNormal(Triangle & t) const {
	auto a = this->vertices[t.a];
	auto b = this->vertices[t.b];
	auto c = this->vertices[t.c];

	auto u = b - a;
	auto v = c - a;

	return u.cross(v).normalize();
}