#include "Layer.h"

namespace gengine {
    namespace graphics {

        Layer::Layer(Renderer2D* renderer, Shader* shader, geometry::mat4 projection_matrix) :renderer(renderer), shader(shader), projection_matrix(projection_matrix)
        {
            this->shader->enable();
            this->shader->setUniformMat4("projection_matrix", this->projection_matrix);
            this->shader->disable();
        }

        Layer::~Layer()
        {
            delete shader;
            delete renderer;

            for (int i = 0; i < this->renderables.size(); i++)
                delete this->renderables[i];
        }

        void Layer::add(Renderable2D* renderable)
        {
            this->renderables.push_back(renderable);
        }

        void Layer::render()
        {
            this->shader->enable();
            this->renderer->begin();
            for (const Renderable2D* renderable : this->renderables)
                renderable->render(this->renderer);
            this->renderer->end();
            this->renderer->flush();
        }
    }
}