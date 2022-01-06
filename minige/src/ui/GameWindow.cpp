#include "GameWindow.hpp"

#include <iostream>
#include <memory>
#include <GL/glew.h>
#include <glfw3.h>
#include "math/vec4.hpp"

namespace gengine {
	using namespace math;

	namespace ui {
#define MAX_KEYS	1024
#define MAX_BUTTONS	32

		struct GameWindow::Impl {
			const char* title;
			int width, height;
			ScreenPosition mousePosition;
			bool keys[MAX_KEYS];
			bool buttons[MAX_BUTTONS];
			GLFWwindow* window = nullptr;
			math::vec4 backgroud;

			static void onWindowResize(GLFWwindow* window, int width, int height) {
				const auto win = static_cast<Impl*>(glfwGetWindowUserPointer(window));
				win->width = width;
				win->height = height;

				/*
				* The glViewport function specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
				* Let (x_nd , y_nd ) be normalized device coordinates.
				* The window coordinates (x_w , y_w ) are then computed as follows:
				* x_w = (x_nd + 1) * width / 2 + x
				* y_w = (y_nd + 1) * height / 2 + y
				*/
				glViewport(0, 0, width, height);
			}

			static void onCursorPositionChange(GLFWwindow* window, double x, double y) {
				const auto win = static_cast<Impl*>(glfwGetWindowUserPointer(window));
				win->mousePosition.x = x;
				win->mousePosition.y = y;
			}

			static void onMouseButtonClick(GLFWwindow* window, int button, int action, int mods) {
				const auto win = static_cast<Impl*>(glfwGetWindowUserPointer(window));
				win->buttons[button] = action != GLFW_RELEASE;
			}

			static void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
				const auto win = static_cast<Impl*>(glfwGetWindowUserPointer(window));
				win->keys[key] = action != GLFW_RELEASE;
			}

			Impl(const char* title, int width, int height) : title(title), width(width), height(height) {
				memset(this->keys, false, sizeof(this->keys));
				memset(this->buttons, false, sizeof(this->buttons));

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

				glfwSetWindowUserPointer(this->window, this);
				glfwSetWindowSizeCallback(this->window, onWindowResize);
				glfwSetCursorPosCallback(this->window, onCursorPositionChange);
				glfwSetMouseButtonCallback(this->window, onMouseButtonClick);
				glfwSetKeyCallback(this->window, onKeyPress);

				// turn off vsync
				glfwSwapInterval(0.0);

				std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

				/* Be sure we do the glew initialization after we have made the context  */
				if (glewInit() != GLEW_OK) {
					throw "Problem: glewInit failed, something is seriously wrong";
				}

				std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
			}

			~Impl() {
				glfwDestroyWindow(this->window);
				glfwTerminate();
			}

			inline bool isKeyPressed(unsigned int keycode) const {
				return keycode >= MAX_KEYS ? false : this->keys[keycode];
			}

			inline bool isMouseButtonPressed(unsigned int button) const {
				return button >= MAX_BUTTONS ? false : this->buttons[button];
			}

			inline const ScreenPosition& getMousePosition() const
			{
				return this->mousePosition;
			}

			void update() const {
				GLenum error = glGetError();
				if (error != GL_NO_ERROR)
					std::cout << "OpenGL Error: " << error << std::endl;

				/*
				* Each window has two rendering buffers; a front buffer and a back buffer.
				* The front buffer is the one being displayed and the back buffer the one you render to.
				* When the entire frame has been rendered, the buffers need to be swapped with one another,
				* so the back buffer becomes the front buffer and vice versa.
				*/
				glfwSwapBuffers(this->window);

				/*
				* GLFW needs to communicate regularly with the window system both in order to receive events
				* and to show that the application hasn't locked up.
				* Event processing must be done regularly while you have visible windows
				* and is normally done each frame after buffer swapping.
				*/
				glfwPollEvents();
			}

			bool isClosed() const {
				return glfwWindowShouldClose(this->window) != 0;
			}

			void clear() const {
				/*
				* Clear the color buffer at the start of the frame
				* Clear the depth buffer at the start of the frame
				*/
				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			}

			void setBackgroundColor(float red, float green, float blue, float alpha) {
				this->backgroud = vec4(red, green, blue, alpha);
			}

			void drawBackgroud() const {
				glClearColor(this->backgroud.x, this->backgroud.y, this->backgroud.z, this->backgroud.w);
			}
		};

		GameWindow::GameWindow(const char* title, int width, int height) : pImpl(std::make_unique<Impl>(title, width, height))
		{
		}

		GameWindow::~GameWindow() = default;

		void GameWindow::update() const
		{
			this->pImpl->update();
		}

		bool GameWindow::isClosed() const
		{
			return this->pImpl->isClosed();
		}

		void GameWindow::clear() const
		{
			this->pImpl->clear();
		}

		void GameWindow::setBackgroundColor(float red, float green, float blue, float alpha)
		{
			this->pImpl->setBackgroundColor(red, green, blue, alpha);
		}

		void GameWindow::drawBackgroud() const
		{
			this->pImpl->drawBackgroud();
		}

		const ScreenPosition& GameWindow::getMousePosition() const
		{
			return this->pImpl->getMousePosition();
		}
	}
}