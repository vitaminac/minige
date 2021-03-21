#include "IndexedVertexBufferObject.h"

namespace gengine {
    namespace graphics {
        IndexedVertexBufferObject::IndexedVertexBufferObject(GLushort* data, GLsizei count)
            : count(count)
        {
            glGenBuffers(1, &vbo_id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        IndexedVertexBufferObject::IndexedVertexBufferObject(GLuint* data, GLsizei count)
            : count(count)
        {
            glGenBuffers(1, &vbo_id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        IndexedVertexBufferObject::~IndexedVertexBufferObject()
        {
            glDeleteBuffers(1, &vbo_id);
        }

        void IndexedVertexBufferObject::bind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
        }

        void IndexedVertexBufferObject::unbind() const
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
}