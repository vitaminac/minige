#include <iostream>
#include "gengine.h"

using namespace gengine;
using namespace graphic;
int main()
{
	const unsigned char *version = glGetString(GL_VERSION);

	Window window("Game Engine", 800, 600);
	glClearColor(0, 0, 1, 1);

	/* I dont know what is it */
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	while (!window.closed()) {
		std::cout << "Window's width: " << window.getWidth() << " window's height: " << window.getHeight() << std::endl;
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