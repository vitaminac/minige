#pragma once
#include <GL/glew.h>

namespace gengine {
    namespace graphics {
        class VertexBufferObject
        {
        private:
            GLuint vbo_id;
            GLuint component_count;
        public:
            VertexBufferObject(GLfloat* data, GLsizei count, GLuint componentCount);
            ~VertexBufferObject();
            void bind() const;
            void unbind() const;

            inline GLuint getComponentCount() const { return component_count; }
        };

        class IndexedVertexBufferObject
        {
        private:
            GLuint vbo_id;
            GLuint count;
        public:
            IndexedVertexBufferObject(GLushort* data, GLsizei count);
            IndexedVertexBufferObject(GLuint* data, GLsizei count);
            ~IndexedVertexBufferObject();
            void bind() const;
            void unbind() const;

            inline GLuint getCount() const { return count; }
        };
    }
}