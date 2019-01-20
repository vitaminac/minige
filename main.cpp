#include <iostream>
#include <fstream>
#include "gengine.h"
#include "test.h"

using namespace gengine;
using namespace graphic;
using namespace geometry;


int main()
{
	auto v = Vec3(1.0, 2.0, 3.0);
	std::cout << v << std::endl;

	auto a = Vec3(1.0, 2.0, 3.0);

	test(a.module(), 3.74166, "3.74166", 0.001);
	std::cout << "The module of " << a << " is " << a.module() << std::endl;

	auto b = Vec3(1.0, 3.0, 5.0);
	test(a + b, Vec3(2, 5, 8), "(1,2,3)+(1,3,5)=(2,5,8)");
	std::cout << a << " + " << b << " = " << a + b << std::endl;
	test(a - b, Vec3(0, -1, -2), "(1,2,3)-(1,3,5)=(0,-1,-2)");
	std::cout << a << " - " << b << " = " << a - b << std::endl;

	test(3 * a, Vec3(3, 6, 9), "3 per (1,2,3) is (3,6,9)");
	std::cout << a << " per 3 is " << a * 3 << std::endl;
	std::cout << "3 per " << a << " is " << 3 * a << std::endl;

	test(-v, Vec3(-1, -2, -3), "The opposite of (1,2,3) is (-1,-2,-3)");
	std::cout << "The opposite of " << v << " is " << -v << std::endl;

	auto u = a.normalize();
	test(u.getX(), 0.267261, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
	test(u.getY(), 0.534522, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
	test(u.getZ(), 0.801784, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
	std::cout << "The unit vector of " << a << " is " << a.normalize() << std::endl;

	test(a.dot(b), 22, "The dot product of (1,2,3) with (1,3,5) is 22", 0);
	std::cout << "The dot product of " << a << " with " << b << " is " << a.dot(b) << std::endl;

	test(a.cross(b), Vec3(1, -2, 1), "The cross product of (1,2,3) with (1,3,5) is (1,-2,1)");
	std::cout << "The cross product of " << a << " with " << b << " is " << a.cross(b) << std::endl;
	test(b.cross(a), Vec3(-1, 2, -1), "The cross product of (1,3,5) with (1,2,3) is (-1,2,-1)");
	std::cout << "The cross product of " << b << " with " << a << " is " << b.cross(a) << std::endl;

	test(a.includedAngle(b), 0.110884, "The angle between (1,2,3) and (1,3,5) is 0.110884", 0.001);
	std::cout << "The angle between " << a << " and " << b << " is " << a.includedAngle(b) << std::endl;

	TriangleMesh mesh;
	std::ifstream off_in("16Triangles.off");
	std::cout << "Reading file 16Triangles.off" << std::endl;
	mesh.importFromOff(off_in);
	std::cout << "The mesh was restored" << std::endl << mesh;

	std::ofstream off_out("16Triangles_out.off");
	std::cout << "Saving as the .off format" << std::endl;
	mesh.saveAsOff(off_out);

	test(mesh.facetArea(mesh.faces[0]), 0.545776, "The surface' area of the Triangle a:6, b:7, c: 8 is 0.545776", 0.0001);
	std::cout << "The surface' area of " << mesh.faces[0] << " is " << mesh.facetArea(mesh.faces[0]) << std::endl;

	test(mesh.surfaceNormal(mesh.faces[0]), Vec3(0, 0, 1), "The surface normal associated with the Triangle a:6, b:7, c: 8 is (0,0,1)");
	std::cout << "The surface normal associated with " << mesh.faces[0] << " is " << mesh.surfaceNormal(mesh.faces[0]) << std::endl;

	test(mesh.vertexNormal(0), Vec3(0, 0, 1), "The vertex normal associated with vectex 0 (0,-0.942809,0) is (0,0,1)");
	std::cout << "The vertex normal associated with vectex 0 " << mesh.vertices[0] << " is " << mesh.vertexNormal(0) << std::endl;

	Mat4 position = Mat4::translation(Vec3(2, 3, 4));
	
	Vec4& c = position.columns[3];
	std::cout << c << std::endl;

	position = position * Mat4::identity();

	c = position.columns[3];
	std::cout << c << std::endl;

	Window window("Game Engine", 800, 600);
	glClearColor(0, 0, 1, 1);

	/* I dont know what is it */
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	while (!window.closed()) {
		std::cout << "Window's width: " << window.getWidth() << " window's height: " << window.getHeight() << std::endl;
		std::cout << "Mouse position: x:" << window.getMousePosition().x << " y: " << window.getMousePosition().y << std::endl;
		window.clear();
#if 1
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
#else
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
#endif
		window.update();
	}
	return 0;
}