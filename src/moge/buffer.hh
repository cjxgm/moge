#pragma once
#include "gl.hh"
#include "meta/resource.hh"
#include "meta/resource-traits.hh"
#include <type_traits>

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

		namespace binding_from_target_detail
		{
			template <GLenum X> using value = std::integral_constant<GLenum, X>;

			template <GLenum TARGET> struct impl;
			template <> struct impl<GL_ARRAY_BUFFER> : value<GL_ARRAY_BUFFER_BINDING> {};
		}
		template <GLenum TARGET>
		constexpr auto binding_from_target =
				binding_from_target_detail::impl<TARGET>::value;
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
		static auto bound()
		{
			constexpr auto binding = buffer_detail::binding_from_target<TARGET>;
			value_type x;
			glGetIntegerv(binding, reinterpret_cast<int*>(&x));
			return x;
		}
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

