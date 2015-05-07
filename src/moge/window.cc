#include "window.hh"
#include "system.hh"
#include "exceptions.hh"
#include "meta/bind.hh"
#include <GLFW/glfw3.h>

namespace moge
{
	namespace window_detail
	{
		namespace
		{
			auto make_window(char const* title, int w, int h)
			{
				auto win = glfwCreateWindow(w, h, title, {}, {});
				if (!win) throw window_failure{"glfw-create-window"};
				return win;
			}

			auto make_window(std::string const& title, glm::ivec2 const& size)
			{
				return glfw::window_uptr{
					make_window(title.c_str(), size.x, size.y),
					&glfwDestroyWindow
				};
			}
		}

		window::window(std::string const& title,
				glm::ivec2 const& size,
				system&)
			: events{std::make_unique<window_events>()}
			, win{make_window(title, size)}
		{
		}

		void window::vsync(bool on)
		{
			meta::bind<window> _(*this);
			glfwSwapInterval(static_cast<int>(on));
		}
	}
}

void meta::bind_traits<moge::window>::bind(value_type const& x)
{
	glfwMakeContextCurrent(x);
};

#ifndef RELEASE
void meta::bind_traits<moge::window>::unbind(value_type const&)
{
	glfwMakeContextCurrent({});
};
#endif

