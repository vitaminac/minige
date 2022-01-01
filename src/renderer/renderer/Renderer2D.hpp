#pragma once
#include <vector>
#include "math/vec3.hpp"
#include "math/mat4.hpp"

namespace gengine {
	namespace renderer {

		struct VertexData
		{
			math::vec3 vertex;
			unsigned int color;
		};

		class Renderable2D; // forward declaration

		class Renderer2D
		{
		protected:
			std::vector<math::mat4> transformations;
			Renderer2D()
			{
				transformations.push_back(math::mat4::identity());
			}
		public:
			virtual ~Renderer2D() = default;
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void flush() = 0;
			virtual void begin() = 0;
			virtual void end() = 0;

			void pushTransform(const math::mat4& transform)
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

			inline const math::mat4& getAccumulatedTransformation() const {
				return transformations.back();
			}
		};
	}
}