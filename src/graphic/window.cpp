#include <iostream>
#include "window.h"

namespace gengine {
	namespace graphic {
		Window::Window(const char * title, int width, int height) :title(title), width(width), height(height)
		{
			if (!glfwInit())
			{
				throw "Initialization failed";
			}
			this->window = glfwCreateWindow(width, height, title, NULL, NULL);
			if (!this->window)
			{
				glfwTerminate();
				throw  "Window or OpenGL context creation failed";
			}
			glfwMakeContextCurrent(this->window);
			glfwSetWindowSizeCallback(window, onWindowResize);

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

			/* Be sure we do the glew initialization after we have made the context  */
			if (glewInit() != GLEW_OK) {
				throw "Problem: glewInit failed, something is seriously wrong";
			}

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
		}

		Window::~Window() {
			glfwDestroyWindow(this->window);
			glfwTerminate();
		}

		void Window::update()
		{
			/*
			* Each window has two rendering buffers; a front buffer and a back buffer.
			* The front buffer is the one being displayed and the back buffer the one you render to.
			* When the entire frame has been rendered, the buffers need to be swapped with one another,
			* so the back buffer becomes the front buffer and vice versa.
			*/
			glfwSwapBuffers(this->window);

			/* This function retrieves the size, in pixels, of the framebuffer of the specified window. If you wish to retrieve the size of the window in screen coordinates */
			// TODO: glfwGetFramebufferSize(this->window, &(this->width), &(this->height));

			/*
			* GLFW needs to communicate regularly with the window system both in order to receive events
			* and to show that the application hasn't locked up.
			* Event processing must be done regularly while you have visible windows
			* and is normally done each frame after buffer swapping.
			*/
			glfwPollEvents();
		}
		bool Window::closed() const
		{
			return glfwWindowShouldClose(this->window) != 0;
		}
		void Window::clear() const
		{
			/*
			* Clear the color buffer at the start of the frame
			* Clear the depth buffer at the start of the frame
			*/
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		}

		void onWindowResize(GLFWwindow * window, int width, int height)
		{
			// TODO: update width and height of Window class

			/*
			* The glViewport function specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
			* Let (x_nd , y_nd ) be normalized device coordinates.
			* The window coordinates (x_w , y_w ) are then computed as follows:
			* x_w = (x_nd + 1) * width / 2 + x
			* y_w = (y_nd + 1) * height / 2 + y
			*/
			glViewport(0, 0, width, height);
		}
	}
}