#include "IndexedVertexBufferObject.hpp"

namespace gengine {
	namespace renderer {
		IndexedVertexBufferObject::IndexedVertexBufferObject(GLuint* data, GLsizei count)
			: count(count)
		{
			glGenBuffers(1, &vbo_id);
			this->bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			this->unbind();
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