#pragma once
#include "gl.hh"
#include "meta/bitmask.hh"
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

namespace moge
{
	namespace misc_detail
	{
		namespace clear_target
		{
			struct tag {};
			using type = bitmask<tag, GLbitfield>;
			constexpr type color_buffer{GL_COLOR_BUFFER_BIT};
			constexpr type depth_buffer{GL_DEPTH_BUFFER_BIT};
		}

		inline void clear_color(glm::vec4 const& color) { glClearColor(color.r, color.g, color.b, color.a); }
		inline void clear(clear_target::type m) { glClear(m.get()); }

		inline void viewport(glm::vec4 const& region) { glViewport(region.x, region.y, region.z, region.w); }
		inline void viewport(glm::vec2 const& size) { viewport({0, 0, size.x, size.y}); }
	}

	namespace clear_target = misc_detail::clear_target;
	using misc_detail::clear_color;
	using misc_detail::clear;
	using misc_detail::viewport;
}

