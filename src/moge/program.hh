#pragma once
#include "gl.hh"
#include "meta/resource.hh"
#include "meta/resource-traits.hh"
#include "shader.hh"
#include <initializer_list>

namespace moge
{
	namespace program_detail
	{
		struct program;
	}

	using program_detail::program;


	template <>
	struct resource_traits<program> : make_resource_traits<GLuint>
	{
		static auto allocate() { return glCreateProgram(); }
		static void deallocate(value_type const& x) { glDeleteProgram(x); }
		static void bind(value_type const& x) { glUseProgram(x); }
		static auto bound()
		{
			value_type x;
			glGetIntegerv(GL_CURRENT_PROGRAM, reinterpret_cast<int*>(&x));
			return x;
		}
	};


	namespace program_detail
	{
		struct program : resource<program>
		{
			template <GLenum ...TYPES>
			program(shader<TYPES> const&... shaders)
				: program{{shaders.get()...}} {}

			program(std::initializer_list<GLuint> const& shaders);
		};
	}
}

