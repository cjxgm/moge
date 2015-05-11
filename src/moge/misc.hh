#pragma once
#include "gl.hh"
#include "meta/bitmask.hh"
#include <glm/vec4.hpp>

namespace moge
{
	namespace misc_detail
	{
		namespace clear_mask
		{
			struct tag {};
			using type = bitmask<tag, GLbitfield>;
			constexpr type color{GL_COLOR_BUFFER_BIT};
			constexpr type depth{GL_DEPTH_BUFFER_BIT};
		}

		void clear_color(glm::vec4 const& color) { glClearColor(color.r, color.g, color.b, color.a); }
		void clear(clear_mask::type m) { glClear(m.get()); }
	}

	namespace clear_mask = misc_detail::clear_mask;
	using misc_detail::clear_color;
	using misc_detail::clear;
}

