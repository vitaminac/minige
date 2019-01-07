#include <iostream>
#include "gengine.h"

using namespace gengine;
using namespace graphic;
int main()
{
	const unsigned char *version = glGetString(GL_VERSION);

	Window window("My Window", 800, 600);
	glClearColor(0, 0, 1, 1);
	while (!window.closed()) {
		std::cout << "Window's width: " << window.getWidth() << " window's height: " << window.getHeight() << std::endl;
		window.clear();
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		window.update();
	}
	return 0;
}