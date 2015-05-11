#pragma once
#include "gl.hh"
#include "meta/resource.hh"
#include "meta/resource-traits.hh"

namespace moge
{
	namespace buffer_detail
	{
		enum struct buffer_usage : GLenum
		{
			static_draw = GL_STATIC_DRAW,
		};

		template <GLenum TARGET> struct buffer;

		using array_buffer = buffer<GL_ARRAY_BUFFER>;
	}

	using buffer_detail::buffer_usage;
	using buffer_detail::      buffer;
	using buffer_detail::array_buffer;


	template <GLenum TARGET>
	struct resource_traits<buffer<TARGET>> : make_resource_traits<GLuint>
	{
		static auto allocate() { value_type x; glGenBuffers(1, &x); return x; }
		static void deallocate(value_type const& x) { glDeleteBuffers(1, &x); }
		static void bind(value_type const& x) { glBindBuffer(TARGET, x); }
	};


	namespace buffer_detail
	{
		template <GLenum TYPE>
		struct buffer : resource<buffer<TYPE>>
		{
			void data(buffer_usage u, void const* data, GLsizeiptr size);
		};

		extern template struct buffer<GL_ARRAY_BUFFER>;
	}
}

