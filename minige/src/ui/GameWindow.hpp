#pragma once
#include "so.h"
#include "Screen.hpp"

namespace gengine {
	namespace ui {
		class SO_API GameWindow {
		public:
			GameWindow(const char* title, int width, int height);
			~GameWindow();
			void update() const;
			bool isClosed() const;
			void clear() const;
			void setBackgroundColor(float red, float green, float blue, float alpha);
			void drawBackgroud() const;
			const ScreenPosition& getMousePosition() const;
		private:
			struct Impl;
			std::unique_ptr<Impl> pImpl;
		};
	}
}