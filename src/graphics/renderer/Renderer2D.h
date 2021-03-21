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
            Renderer2D()
            {
                transformations.push_back(geometry::mat4::identity());
            }
        public:
            virtual ~Renderer2D() = default;
            virtual void submit(const Renderable2D* renderable) = 0;
            virtual void flush() = 0;
            virtual void begin() = 0;
            virtual void end() = 0;

            void pushTransform(const geometry::mat4& transform)
            {
                transformations.push_back(transformations.back() * transform);
            }

            void popTransform()
            {
                if (transformations.size() > 1) {
                    transformations.pop_back();
                }
                else {
                    throw "Renderer2D popTransform when size <= 1";
                }
            }

            inline const geometry::mat4& getAccumulatedTransformation() const {
                return transformations.back();
            }
        };
    }
}