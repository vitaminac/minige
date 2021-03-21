#pragma once
#include "renderable2d.h"
#include "../renderer/Renderer2d.h"

namespace gengine {
    namespace graphics {

        class Group : public Renderable2D
        {
        private:
            std::vector<Renderable2D*> children;
            geometry::mat4 transform;
        public:
            Group(const geometry::mat4& transform);
            void add(Renderable2D* renderable);
            virtual void render(Renderer2D* renderer) const override;
        };
    }
}