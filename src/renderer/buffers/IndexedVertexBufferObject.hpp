#pragma once
#include <GL/glew.h>

namespace gengine {
	namespace renderer {
		class IndexedVertexBufferObject
		{
		private:
			GLuint vbo_id;
			GLuint count;
		public:
			IndexedVertexBufferObject(GLuint* data, GLsizei count);
			~IndexedVertexBufferObject();
			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return count; }
		};
	}
}