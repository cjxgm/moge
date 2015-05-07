#pragma once
#include <memory>
#include <string>
#include <glm/vec2.hpp>
#include "meta/bind-traits.hh"
#include "system.hh"

struct GLFWwindow;

namespace moge
{
	namespace window_detail
	{
		namespace glfw
		{
			using window = GLFWwindow;
			using window_deleter = void (window *);
			using window_uptr = std::unique_ptr<window, window_deleter*>;
		}

		struct window_events
		{
			using self = window_events;
			using uptr = std::unique_ptr<self>;
		};

		struct window
		{
			window_events::uptr events;

			window(std::string const& title={"moge"},
					glm::ivec2 const& size ={16*60, 9*60},
					system& = system::instance());

			void vsync(bool on=true);

			operator auto () const { return win.get(); }

		private:
			glfw::window_uptr win;
		};
	}

	using window_detail::window;
}

template <>
struct meta::bind_traits<moge::window>
{
	using value_type = moge::window_detail::glfw::window*;
	static void bind(value_type const& x);
	static void unbind(value_type const&)
#ifdef RELEASE
	{}
#else
	;
#endif
};
