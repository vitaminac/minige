#pragma once
#include "so.h"
#include "../Shader.hpp"
#include "Renderable2D.hpp"

namespace gengine {
	namespace renderer {

		class SO_API Layer
		{
		protected:
			Renderer2D* renderer;
			std::vector<Renderable2D*> renderables;
			Shader* shader;
			math::mat4 projection_matrix;
		protected:
			Layer(Renderer2D* renderer, Shader* shader, math::mat4 projectionMatrix);
		public:
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();
		};
	}
}