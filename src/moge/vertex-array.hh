#pragma once
#include "gl.hh"
#include "meta/resource.hh"
#include "meta/resource-traits.hh"

namespace moge
{
	namespace vertex_array_detail
	{
		struct vertex_array;
	}

	using vertex_array_detail::vertex_array;


	template <>
	struct resource_traits<vertex_array> : make_resource_traits<GLuint>
	{
		static auto allocate() { value_type x; glGenVertexArrays(1, &x); return x; }
		static void deallocate(value_type const& x) { glDeleteVertexArrays(1, &x); }
		static void bind(value_type const& x) { glBindVertexArray(x); }
		static auto bound()
		{
			value_type x;
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, reinterpret_cast<int*>(&x));
			return x;
		}
	};


	namespace vertex_array_detail
	{
		struct vertex_array : resource<vertex_array>
		{
			auto& draw_point(GLsizei count, int first=0)
			{
				return draw<GL_POINTS>(count, first);
			}

			auto& draw_line_loop(GLsizei count, int first=0)
			{
				return draw<GL_LINE_LOOP>(count, first);
			}

			auto& draw_triangle(GLsizei count, int first=0)
			{
				return draw<GL_TRIANGLES>(count, first);
			}

			auto& draw_triangle_strip(GLsizei count, int first=0)
			{
				return draw<GL_TRIANGLE_STRIP>(count, first);
			}

		private:
			template <GLenum MODE>
			vertex_array& draw(GLsizei count, int first=0)
			{
				auto _ = bind();
				glDrawArrays(MODE, first, count);
				return *this;
			}
		};
	}
}

