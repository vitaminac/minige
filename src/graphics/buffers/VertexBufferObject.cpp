#include "VertexBufferObject.h"

namespace gengine {
    namespace graphics {
        VertexBufferObject::VertexBufferObject(GLfloat* data, GLsizeiptr size, GLenum usage)
        {
            glGenBuffers(1, &vbo_id);
            this->bind();
            // Passing data
            glBufferData(GL_ARRAY_BUFFER, size, data, usage);
            this->unbind();
        }

        VertexBufferObject::~VertexBufferObject()
        {
            glDeleteBuffers(1, &vbo_id);
        }

        void VertexBufferObject::bind() const
        {
            // bind as a global pointer that glVertexAttribPointer reads
            glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
        }

        void VertexBufferObject::unbind() const
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}

