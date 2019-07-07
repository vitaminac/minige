#include "vbo.h"

namespace gengine {
    namespace graphic {
        // TODO: what is difference of count and componentCount
        VertexBufferObject::VertexBufferObject(GLfloat* data, GLsizei count, GLuint componentCount) : component_count(componentCount)
        {
            // Create a VBO
            glGenBuffers(1, &vbo_id);
            // Specify the type
            glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
            // Passing data
            glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
            // Once is done unbind the buffer
            glBindBuffer(GL_ARRAY_BUFFER, 0);
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
            // unbind the context
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

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

