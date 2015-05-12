#pragma once
#include "gl.hh"
#include <glm/fwd.hpp>
#include <type_traits>

namespace moge
{
	namespace gl_traits_detail
	{
		namespace type_to_enum_detail
		{
			template <GLenum X>
			using value = std::integral_constant<GLenum, X>;

			template <class T> struct impl;
			template <> struct impl<char  > : value<GL_BYTE  > {};
			template <> struct impl<short > : value<GL_SHORT > {};
			template <> struct impl<int   > : value<GL_INT   > {};
			template <> struct impl<float > : value<GL_FLOAT > {};
			template <> struct impl<double> : value<GL_DOUBLE> {};
			template <> struct impl<unsigned char > : value<GL_UNSIGNED_BYTE > {};
			template <> struct impl<unsigned short> : value<GL_UNSIGNED_SHORT> {};
			template <> struct impl<unsigned int  > : value<GL_UNSIGNED_INT  > {};
		}
		template <class T>
		constexpr auto type_to_enum = type_to_enum_detail::impl<T>::value;

		namespace should_normalize_detail
		{
			template <class T> constexpr auto should_normalize = false;
			template <> constexpr auto should_normalize<char> = true;
			template <> constexpr auto should_normalize<unsigned char> = true;
		}
		using should_normalize_detail::should_normalize;

		template <GLint NCOMPONENT, class T, bool NORMALIZE>
		struct value
		{
			enum : GLint  { ncomponent = NCOMPONENT };
			enum : GLenum { type_enum  = type_to_enum<T> };
			enum : bool   { normalize  = NORMALIZE  };
		};

		template <class T> struct gl_traits;

		template <class T, glm::precision P>
		struct gl_traits<glm::tvec1<T, P>> : value<1, T, should_normalize<T>> {};
		template <class T, glm::precision P>
		struct gl_traits<glm::tvec2<T, P>> : value<2, T, should_normalize<T>> {};
		template <class T, glm::precision P>
		struct gl_traits<glm::tvec3<T, P>> : value<3, T, should_normalize<T>> {};
		template <class T, glm::precision P>
		struct gl_traits<glm::tvec4<T, P>> : value<4, T, should_normalize<T>> {};
	}

	using gl_traits_detail::gl_traits;
}

