#pragma once
#include "gl.hh"
#include <glm/fwd.hpp>
#include <type_traits>

namespace moge
{
	namespace gl_traits_detail
	{
		namespace gl_type_to_enum_detail
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
			template <> struct impl<glm::vec2> : value<GL_FLOAT_VEC2> {};
			template <> struct impl<glm::vec3> : value<GL_FLOAT_VEC3> {};
			template <> struct impl<glm::vec4> : value<GL_FLOAT_VEC4> {};
			template <> struct impl<glm::mat2> : value<GL_FLOAT_MAT2> {};
			template <> struct impl<glm::mat3> : value<GL_FLOAT_MAT3> {};
			template <> struct impl<glm::mat4> : value<GL_FLOAT_MAT4> {};

			template <class T>
			constexpr auto gl_type_to_enum = impl<T>::value;
		}
		using gl_type_to_enum_detail::gl_type_to_enum;


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
			enum : GLenum { type_enum  = gl_type_to_enum<T> };
			enum : bool   { normalize  = NORMALIZE  };
		};

		template <class T> struct gl_traits;

		template <> struct gl_traits<char  > : value<1,   char, should_normalize<  char>> {};
		template <> struct gl_traits<short > : value<1,  short, should_normalize< short>> {};
		template <> struct gl_traits<int   > : value<1,    int, should_normalize<   int>> {};
		template <> struct gl_traits<float > : value<1,  float, should_normalize< float>> {};
		template <> struct gl_traits<double> : value<1, double, should_normalize<double>> {};
		template <> struct gl_traits<unsigned char > : value<1, unsigned  char, should_normalize<unsigned  char>> {};
		template <> struct gl_traits<unsigned short> : value<1, unsigned short, should_normalize<unsigned short>> {};
		template <> struct gl_traits<unsigned int  > : value<1, unsigned   int, should_normalize<unsigned   int>> {};

		template <class T, glm::precision P>
		struct gl_traits<glm::tvec2<T, P>> : value<2, T, should_normalize<T>> {};
		template <class T, glm::precision P>
		struct gl_traits<glm::tvec3<T, P>> : value<3, T, should_normalize<T>> {};
		template <class T, glm::precision P>
		struct gl_traits<glm::tvec4<T, P>> : value<4, T, should_normalize<T>> {};
		template <class T, glm::precision P>
		struct gl_traits<glm::tmat2x2<T, P>> : value<2*2, T, should_normalize<T>> {};
		template <class T, glm::precision P>
		struct gl_traits<glm::tmat3x3<T, P>> : value<3*3, T, should_normalize<T>> {};
		template <class T, glm::precision P>
		struct gl_traits<glm::tmat4x4<T, P>> : value<4*4, T, should_normalize<T>> {};
	}

	using gl_traits_detail::gl_traits;
	using gl_traits_detail::gl_type_to_enum;
}

