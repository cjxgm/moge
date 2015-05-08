#pragma once
#include <memory>
#include <string>
#include <glm/vec2.hpp>
#include <functional>
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

			using close_func = std::function<void ()>;
			close_func close;
		};

		struct window
		{
			window_events::uptr events;

			window(std::string const& title={"moge"},
					glm::ivec2 const& size ={16*60, 9*60},
					system& = system::instance());

			void vsync(bool on=true);
			void update();

			operator auto () const { return win.get(); }

		private:
			glfw::window_uptr win;
		};
	}

	using window_detail::window;

	template <>
	struct bind_traits<window>
		: make_bind_traits<window_detail::glfw::window*>
	{
		static void bind(value_type const& x);
	};
}

