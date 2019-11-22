#include <iostream>
#include <fstream>
#include <time.h>

#include "gengine.h"
#include "test.h"

#include <FreeImage.h>

using namespace gengine;
using namespace graphics;
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

void test_free_image() {
    const char* filename = "test.png";

    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

    //pointer to the image, once loaded
    FIBITMAP* dib(0);

    //pointer to the image data
    BYTE* bits(0);

    //image width and height
    unsigned int width(0), height(0);

    //OpenGL's image ID to map to
    GLuint gl_texID;

    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);

    //if still unknown, try to guess the file format from the file extension
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);

    //if still unkown, return failure
    if (fif == FIF_UNKNOWN)
        throw "unknow format";

    //check that the plugin has reading capabilities and load the file
    if (FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename);

    //if the image failed to load, return failure
    if (!dib)
        throw "load image data failed";

    //retrieve the image data
    bits = FreeImage_GetBits(dib);
    unsigned int bitsPerPixel = FreeImage_GetBPP(dib);
    unsigned int bytesPerPixel = bitsPerPixel / 8;
    unsigned int pitch = FreeImage_GetPitch(dib);

    //get the image width and height
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);

    //if this somehow one of these failed (they shouldn't), return failure
    if ((bits == 0) || (width == 0) || (height == 0))
        throw "load image extras data failed";

    for (int y = height - 1; y >= 0; y--)
    {
        BYTE* pixel = ((BYTE*)bits) + y * pitch;
        for (int x = 0; x < width; x++)
        {
            std::cout << +pixel[FI_RGBA_RED] << " " << + pixel[FI_RGBA_GREEN] << " " << + pixel[FI_RGBA_BLUE] << std::endl;
            pixel += bytesPerPixel;
        }
    }
    FreeImage_Unload(dib);
}

int main()
{
    // test
    test_vector();
    test_mesh();
    test_mat4();
    test_file_utils();
    test_free_image();

    const int window_width = 960;
    const int window_height = 540;
    Window window("Game Engine", window_width, window_height);
    window.setBackgroundColor(1.0f, 1.0f, 1.0f, 1.0f);
    window.drawBackgroud();

    const float content_width = 16;
    const float content_height = 9;

    Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    Shader* s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    Shader& shader = *s;
    Shader& shader2 = *s2;

    TileLayer layer(s, content_width, content_height);
    shader.enable(); // TODO : delete?
    srand(time(NULL));

    for (float y = 0; y < content_height; y += 0.05)
    {
        for (float x = 0; x < content_width; x += 0.05)
        {
            layer.add(new Sprite(x, y, 0.04f, 0.04f, vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
        }
    }

    TileLayer panel(s2, content_width, content_height);
    Group* group = new Group(mat4::translation(geometry::vec3(0.0f, 0.0f, 0.0f)));
    group->add(new Sprite(0, 0, 5, 5, geometry::vec4(0, 0, 1, 1)));
    Group* button = new Group(mat4::translation(vec3(5.0f, 5.0f, 0.0f)));
    button->add(new Sprite(0, 0, 2.5f, 2.0f, geometry::vec4(1, 0, 0, 1)));
    button->add(new Sprite(2.5, 0, 2.5f, 2.0f, geometry::vec4(0, 1, 0, 1)));
    group->add(button);
    panel.add(group);

    // select active texture unit
    glActiveTexture(GL_TEXTURE1);
    Texture texture("test.png");
    texture.bind();

    shader.enable();
    shader.setUniformInteger("tex", 1);
    shader.disable();

    auto initial_position = vec2(4.0f, 5.0f);
    shader2.enable();
    shader2.setUniformVector2("light_position", initial_position);

    Timer timer;
    unsigned int frames = 0;
    while (!window.closed()) {
        window.clear();
        auto& p = window.getMousePosition();
        shader.enable();
        shader.setUniformVector2("light_position", vec2((float)(p.x * content_width / window_width), (float)(content_height - p.y * content_height / window_height)));
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
    return 0;
}