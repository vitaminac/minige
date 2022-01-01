#include "VertexArrayObject.hpp"

namespace gengine {
	namespace renderer {

		VertexArrayObject::VertexArrayObject()
		{
			// Create single VAO which contains the vertex array state
			glGenVertexArrays(1, &vao_id);
		}

		VertexArrayObject::~VertexArrayObject()
		{
			glDeleteVertexArrays(1, &vao_id);
		}

		void VertexArrayObject::bind() const
		{
			glBindVertexArray(vao_id);
		}

		void VertexArrayObject::unbind() const
		{
			glBindVertexArray(0);
		}

		void VertexArrayObject::addBuffer(VertexBufferObject* buffer, GLuint index, GLint componentCount, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
			this->bind();
			buffer->bind();

			// Enables the generic vertex attribute specified by index for use in drawing
			glEnableVertexAttribArray(index);

			/*
			The association between a buffer object and a vertex attribute
			happens when you call glVertexAttribPointer
			*/

			/*
			When you call glVertexAttribPointer,
			OpenGL takes whatever buffer is at the moment
			of this call bound to GL_ARRAY_BUFFER
			and associates it with the given vertex attribute.
			*/

			// Specify format of a VBO, put that information in the VAO
			glVertexAttribPointer(index, componentCount, type, normalized, stride, offset);

			buffer->unbind();
			this->unbind();
		}
	}
}