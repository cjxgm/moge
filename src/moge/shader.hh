#pragma once
#include "gl.hh"
#include "meta/resource.hh"
#include "meta/resource-traits.hh"
#include <string>

namespace moge
{
	namespace shader_detail
	{
		template <GLenum TYPE> struct shader;

		using   vertex_shader = shader<GL_VERTEX_SHADER  >;
		using geometry_shader = shader<GL_GEOMETRY_SHADER>;
		using fragment_shader = shader<GL_FRAGMENT_SHADER>;
	}

	using shader_detail::         shader;
	using shader_detail::  vertex_shader;
	using shader_detail::geometry_shader;
	using shader_detail::fragment_shader;


	template <GLenum TYPE>
	struct resource_traits<shader<TYPE>> : make_resource_traits<GLuint>
	{
		static auto allocate() { return glCreateShader(TYPE); }
		static void deallocate(value_type const& x) { glDeleteShader(x); }
	};

	namespace shader_detail
	{
		template <GLenum TYPE>
		struct shader : resource<shader<TYPE>>
		{
			shader(std::string const& source);
		};

		extern template struct shader<GL_VERTEX_SHADER  >;
		extern template struct shader<GL_GEOMETRY_SHADER>;
		extern template struct shader<GL_FRAGMENT_SHADER>;
	}
}

