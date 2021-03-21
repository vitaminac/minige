#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "common.h"
#include "geometry/vec4.h"

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

using namespace gengine::geometry;

namespace gengine {
    namespace graphics {
        class GameWindow {
        private:
            const char* title;
            int width, height;
            Position position;
            bool keys[MAX_KEYS];
            bool buttons[MAX_BUTTONS];
            GLFWwindow* window = nullptr;
            vec4 backgroud;

            friend static void onCursorPositionChange(GLFWwindow* window, double x, double y);
            friend static void onWindowResize(GLFWwindow* window, int width, int height);
            friend static void onMouseButtonClick(GLFWwindow* window, int button, int action, int mods);
            friend static void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);

        public:
            GameWindow(const char* title, int width, int height);
            ~GameWindow();
            void update();
            bool closed() const;
            void clear() const;
            void setBackgroundColor(float red, float green, float blue, float alpha);
            void drawBackgroud();

            inline int getWidth() const { return this->width; }

            inline int getHeight() const { return this->height; }

            inline const Position& getMousePosition() const { return this->position; }

            inline bool isKeyPressed(unsigned int keycode) const {
                return keycode >= MAX_KEYS ? false : this->keys[keycode];
            }

            inline bool isMouseButtonPressed(unsigned int button) const {
                return button >= MAX_BUTTONS ? false : this->buttons[button];
            }
        };
    }
}