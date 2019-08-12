#pragma once

#include <vector>
#include <GL/glew.h>
#include "geometry/geometry.h"

namespace gengine {
    namespace graphics {

        class Renderable2D; // forward declaration

        class Renderer2D
        {
        protected:
            std::vector<geometry::mat4> transformations;
            const geometry::mat4* accumulated_transformation;
            Renderer2D()
            {
                transformations.push_back(geometry::mat4::identity());
                accumulated_transformation = &transformations.back();
            }
        public:
            virtual void submit(const Renderable2D* renderable) = 0;
            virtual void flush() = 0;
            virtual void begin() {}
            virtual void end() {}

            void push(const geometry::mat4& matrix, bool override = false)
            {
                if (override)
                    transformations.push_back(matrix);
                else
                    transformations.push_back(transformations.back() * matrix);

                accumulated_transformation = &transformations.back();
            }

            void pop()
            {
                // TODO: Add to log!
                if (transformations.size() > 1)
                    transformations.pop_back();

                accumulated_transformation = &transformations.back();
            }
        };
    }
}