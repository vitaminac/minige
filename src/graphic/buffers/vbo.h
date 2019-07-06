#pragma once
#include <GL/glew.h>

namespace gengine {
    namespace graphic {
        class VertexBufferObject
        {
        private:
            GLuint vbo_id;
            GLuint component_count;
        public:
            VertexBufferObject(GLfloat* data, GLsizei count, GLuint componentCount);

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

            void bind() const;
            void unbind() const;

            inline GLuint getCount() const { return count; }
        };
    }
}