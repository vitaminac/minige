#include <iostream>
#include <fstream>
#include "gengine.h"
#include "test.h"

using namespace gengine;
using namespace graphic;
using namespace geometry;

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
    test(u.getX(), 0.267261, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
    test(u.getY(), 0.534522, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
    test(u.getZ(), 0.801784, "The unit vector of (1,2,3) is (0.267261,0.534522,0.801784)", 0.001);
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

int main()
{
    test_vector();
    test_mesh();
    test_mat4();
    test_file_utils();

    Window window("Game Engine", 800, 600);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    GLfloat vertices[] = {
        0, 0, 0,
        8, 0, 0,
        0, 3, 0,
        0, 3, 0,
        8, 3, 0,
        8, 0, 0
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    mat4 ortho = mat4::orthographic(vec3(0.0f, 0.0f, -1.0f), vec3(16.0f, 9.0f, 1.0f));

    Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    shader.enable();
    shader.setUniformMat4("projection_matrix", ortho);
    shader.setUniformMat4("model_matrix", mat4::rotation(vec3::FORWARD, 10.0f) * mat4::translation(vec3(4, 3, 0)));
    shader.setUniformVector2("light_position", vec2(4.0f, 1.5f));
    shader.setUniformVector4("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

    while (!window.closed()) {
        window.clear();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        window.update();
    }
    return 0;
}