#pragma once
#include "../renderer2d.h"
#include "../renderable2d.h"

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