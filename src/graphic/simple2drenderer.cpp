#include "simple2drenderer.h"

namespace gengine {
    namespace graphic {

        void Simple2DRenderer::submit(const Renderable2D* renderable)
        {
            queue.push_back(renderable);
        }

        void Simple2DRenderer::flush()
        {
            while (!queue.empty())
            {
                const Renderable2D* renderable = queue.front();
                renderable->getVAO()->bind();
                renderable->getIBO()->bind();

                renderable->getShader().setUniformMat4("model_matrix", mat4::translation(renderable->getPosition()));
                glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

                renderable->getIBO()->unbind();
                renderable->getVAO()->unbind();

                queue.pop_front();
            }
        }
    }
}