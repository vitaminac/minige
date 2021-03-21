#pragma once
#include "../Shader.h"
#include "Renderable2D.h"

namespace gengine {
    namespace graphics {

        class Layer
        {
        protected:
            Renderer2D* renderer;
            std::vector<Renderable2D*> renderables;
            Shader* shader;
            geometry::mat4 projection_matrix;
        protected:
            Layer(Renderer2D* renderer, Shader* shader, geometry::mat4 projectionMatrix);
        public:
            virtual ~Layer();
            virtual void add(Renderable2D* renderable);
            virtual void render();
        };
    }
}