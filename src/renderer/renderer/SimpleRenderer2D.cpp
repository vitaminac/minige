#include "SimpleRenderer2D.hpp"

namespace gengine {
	using namespace math;

	namespace renderer {

		void Simple2DRenderer2D::submit(const Renderable2D* renderable)
		{
			queue.push_back(static_cast<const StaticSprite*>(renderable));
		}

		void Simple2DRenderer2D::flush()
		{
			while (!queue.empty())
			{
				const StaticSprite* sprite = queue.front();
				sprite->getVAO()->bind();
				sprite->getIBO()->bind();

				sprite->getShader().setUniformMat4("model_matrix", mat4::translation(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_INT, nullptr);

				sprite->getIBO()->unbind();
				sprite->getVAO()->unbind();

				queue.pop_front();
			}
		}

		void Simple2DRenderer2D::begin()
		{
		}

		void Simple2DRenderer2D::end()
		{
		}
	}
}