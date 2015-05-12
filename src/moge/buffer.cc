#include "buffer.hh"

namespace moge
{
	namespace buffer_detail
	{
		template <GLenum TARGET>
		void buffer<TARGET>::data(buffer_usage u, void const* data, GLsizeiptr size)
		{
			this->bind();
			glBufferData(TARGET, size, data, static_cast<GLenum>(u));
		}

		template struct buffer<GL_ARRAY_BUFFER>;
	}
}

