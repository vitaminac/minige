#include "group.h"

namespace gengine {
    namespace graphics {
        Group::Group(const geometry::mat4& transform) : transform(transform)
        {
        }

        void Group::add(Renderable2D* renderable)
        {
            this->children.push_back(renderable);
        }

        void Group::submit(Renderer2D* renderer) const
        {
            renderer->push(this->transform);

            for (const Renderable2D* renderable : children)
                renderable->submit(renderer);

            renderer->pop();
        }
    }
}