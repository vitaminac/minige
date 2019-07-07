#include "simple2drenderer.h"

namespace gengine {
    namespace graphic {

        void Simple2DRenderer::submit(const Renderable2D* renderable)
        {
            queue.push_back(static_cast<const StaticSprite*>(renderable));
        }

        void Simple2DRenderer::flush()
        {
            while (!queue.empty())
            {
                const StaticSprite* sprite = queue.front();
                sprite->getVAO()->bind();
                sprite->getIBO()->bind();

                sprite->getShader().setUniformMat4("model_matrix", mat4::translation(sprite->getPosition()));
                glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

                sprite->getIBO()->unbind();
                sprite->getVAO()->unbind();

                queue.pop_front();
            }
        }
    }
}