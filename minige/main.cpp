#include <iostream>
#include <fstream>
#include <time.h>

#include <FreeImage.h>

#include "math/vec3.hpp"
#include "math/vec4.hpp"
#include "math/mat4.hpp"
#include "math/mesh.hpp"
#include "physics/light.hpp"
#include "platform/FileUtils.hpp"
#include "platform/Image.hpp"
#include "platform/Timer.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"
#include "renderer/renderable/Group.hpp"
#include "renderer/renderable/StaticSprite.hpp"
#include "renderer/renderable/TileLayer.hpp"
#include "renderer/renderer/SimpleRenderer2D.hpp"
#include "ui/GameWindow.hpp"
#include "test.h"

using namespace gengine;
using namespace math;
using namespace physics;
using namespace platform;
using namespace renderer;
using namespace ui;

void test_vector() {
	auto v = vec3(1.0, 2.0, 3.0);
	std::cout << v << std::endl;

	auto a = vec3(1.0, 2.0, 3.0);

	test(a.module(), 3.74166, "3.74166", 0.001);
	std::cout << "The module of " << a << " is " << a.module() << std::endl;

	auto b = vec3(1.0, 3.0, 5.0);
	test(a + b, vec3(2, 5, 8), "(1,2,3)+(1,3,5)=(2,5,8)");
	std::cout << a << " + " << b << " = " << a + b << std::endl;
	test(a - b, vec3(0, -1, -2), "(1,2,3)-(1,3,5)=(0,-1,-2)");
	std::cout << a << " - " << b << " = " << a - b << std::endl;

	test(3 * a, vec3(3, 6, 9), "3 per (1,2,3) is (3,6,9)");
	std::cout << a << " per 3 is " << a * 3 << std::endl;
	std::cout << "3 per " << a << " is " << 3 * a << std::endl;

	test(-v, vec3(-1, -2, -3), "The opposite of (1,2,3) is (-1,-2,-3)");
	std::cout << "The opposite of " << v << " is " << -v << std::endl;

	auto u = a.normalize();
	test(u.x, 0.267261, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
	test(u.y, 0.534522, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
	test(u.z, 0.801784, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
	std::cout << "The unit vector of " << a << " is " << a.normalize() << std::endl;

	test(a.dot(b), 22, "The dot product of (1,2,3) with (1,3,5) is 22", 0);
	std::cout << "The dot product of " << a << " with " << b << " is " << a.dot(b) << std::endl;

	test(a.cross(b), vec3(1, -2, 1), "The cross product of (1,2,3) with (1,3,5) is (1,-2,1)");
	std::cout << "The cross product of " << a << " with " << b << " is " << a.cross(b) << std::endl;
	test(b.cross(a), vec3(-1, 2, -1), "The cross product of (1,3,5) with (1,2,3) is (-1,2,-1)");
	std::cout << "The cross product of " << b << " with " << a << " is " << b.cross(a) << std::endl;

	test(a.includedAngle(b), 0.110884, "The angle between (1,2,3) and (1,3,5) is 0.110884", 0.001);
	std::cout << "The angle between " << a << " and " << b << " is " << a.includedAngle(b) << std::endl;

}

void test_mesh() {
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

	test(mesh.surfaceNormal(mesh.faces[0]), vec3(0, 0, 1), "The surface normal associated with the Triangle a:6, b:7, c: 8 is (0,0,1)");
	std::cout << "The surface normal associated with " << mesh.faces[0] << " is " << mesh.surfaceNormal(mesh.faces[0]) << std::endl;

	test(mesh.vertexNormal(0), vec3(0, 0, 1), "The vertex normal associated with vectex 0 (0,-0.942809,0) is (0,0,1)");
	std::cout << "The vertex normal associated with vectex 0 " << mesh.vertices[0] << " is " << mesh.vertexNormal(0) << std::endl;

}

void test_mat4() {
	mat4 position = mat4::translation(vec3(2, 3, 4));

	vec4& c = position.columns[3];
	std::cout << c << std::endl;

	position = position * mat4::identity();

	c = position.columns[3];
	std::cout << c << std::endl;
}

void test_file_utils() {
	std::string cpp = FileUtils::read_file("main.cpp");
	std::cout << cpp << std::endl;
}

void test_simple_renderer() {
	const int window_width = 960;
	const int window_height = 540;
	GameWindow window("Test Simple Renderer", window_width, window_height);
	window.setBackgroundColor(1.0f, 1.0f, 1.0f, 1.0f);

	const float content_width = 16;
	const float content_height = 9;
	mat4 ortho = mat4::orthographic(0.0f, content_width, 0.0f, content_height, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("projection_matrix", ortho);

	StaticSprite sprite(5, 5, 4, 4, vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 2, 3, vec4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer2D renderer;

	struct Light light = {
		vec2(0.0f, 0.0f)
	};

	while (!window.closed())
	{
		window.clear();
		auto& p = window.getMousePosition();
		light.position = vec2((float)(p.x * content_width / window_width), (float)(content_height - p.y * content_height / window_height));
		shader.setLight("light", light);

		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.flush();

		window.update();
	}
}

void test_batch_renderer_tilelayer() {
	const int window_width = 960;
	const int window_height = 540;
	GameWindow window("Test Batch Renderer", window_width, window_height);
	window.setBackgroundColor(1.0f, 1.0f, 1.0f, 1.0f);
	window.drawBackgroud();

	const float content_width = 16;
	const float content_height = 9;

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/texture.frag");
	Shader* s2 = new Shader("src/shaders/basic.vert", "src/shaders/texture.frag");
	Shader& shader = *s;
	Shader& shader2 = *s2;

	TileLayer layer(s, content_width, content_height);
	srand(time(NULL));

	for (float y = 0; y < content_height; y += 0.05)
	{
		for (float x = 0; x < content_width; x += 0.05)
		{
			layer.add(new Sprite(x, y, 0.04f, 0.04f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}

	TileLayer panel(s2, content_width, content_height);
	Group* group = new Group(mat4::translation(vec3(0.0f, 0.0f, 0.0f)));
	group->add(new Sprite(0, 0, 5, 5, vec4(0, 0, 1, 1)));
	Group* button = new Group(mat4::translation(vec3(5.0f, 5.0f, 0.0f)));
	button->add(new Sprite(0, 0, 2.5f, 2.0f, vec4(1, 0, 0, 1)));
	button->add(new Sprite(2.5, 0, 2.5f, 2.0f, vec4(0, 1, 0, 1)));
	group->add(button);
	panel.add(group);

	// select active texture unit
	glActiveTexture(GL_TEXTURE1);
	Image image("test.png");
	Texture texture(&image);
	texture.bind();

	shader.enable();
	shader.setUniformInteger("tex", 1);
	shader.disable();

	auto initial_position = vec2(4.0f, 5.0f);
	struct Light light = {
		initial_position
	};
	shader2.enable();
	shader2.setLight("light", light);

	Timer timer;
	unsigned int frames = 0;
	while (!window.closed()) {
		window.clear();
		auto& p = window.getMousePosition();
		light.position = vec2((float)(p.x * content_width / window_width), (float)(content_height - p.y * content_height / window_height));
		shader.enable();
		shader.setLight("light", light);
		layer.render();

		panel.render();
		window.update();
		frames++;
		if (timer.elapsed() > 1) {
			printf("fps: %d\n", frames);
			frames = 0;
			timer.reset();
		}
	}
}

int main()
{
	// test
	test_vector();
	test_mesh();
	test_mat4();
	test_file_utils();
	test_simple_renderer();
	test_batch_renderer_tilelayer();

	return 0;
}