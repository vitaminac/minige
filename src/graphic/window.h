#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace gengine {
	namespace graphic {
		class Window {
		private:
			const char *title;
			int width, height;
			GLFWwindow *window = NULL;
		public:
			Window(const char *title, int width, int height);
			~Window();
			void update();
			bool closed() const;
			void clear() const;
			inline int getWidth() const { return this->width; }
			inline int getHeight() const { return this->height; }
		};
		void onWindowResize(GLFWwindow* window, int width, int height);
	}
}