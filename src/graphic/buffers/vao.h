#pragma once
#include <vector>
#include <GL/glew.h>

#include "./vbo.h"

namespace gengine {
    namespace graphic {
        /**
        VAOs do store which buffer objects are associated with which attributes

        Up until now, every time we have attempted to draw anything,
        we needed to do certain setup work before the draw call.
        In particular, we have to do the following,
        for each vertex attribute used by the vertex shader:
        1. Use glEnableVertexAttribArray to enable this attribute.
        2. Use glBindBuffer(GL_ARRAY_BUFFER) to bind to the context
            the buffer object that contains the data for this attribute.
        3. Use glVertexAttribPointer to define
            the format of the data for the attribute
            within the buffer object previously
            bound to GL_ARRAY_BUFFER.
         */
        class VertexArrayObject
        {
        private:
            GLuint vao_id;
            std::vector<VertexBufferObject*> buffers;
        public:
            VertexArrayObject();
            ~VertexArrayObject();

            void addBuffer(VertexBufferObject* buffer, GLuint index);
            void bind() const;
            void unbind() const;
        };
    }
}