#include "window.hh"
#include "system.hh"
#include "exceptions.hh"
#include "meta/bind.hh"
#include <GLFW/glfw3.h>
#include <utility>		// for std::forward

namespace moge
{
	namespace window_detail
	{
		namespace
		{
			auto make_window(char const* title, int w, int h)
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

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

			auto& events_from_window(glfw::window* win)
			{
				auto up = glfwGetWindowUserPointer(win);
				auto ev = reinterpret_cast<window_events*>(up);
				return *ev;
			}

			template <class F, class ...ARGS>
			void safe_call(F const& f, ARGS &&... args)
			{
				if (f) return f(std::forward<ARGS>(args)...);
			}
		}

		window::window(std::string const& title,
				glm::ivec2 const& size,
				system&)
			: events{std::make_unique<window_events>()}
			, win{make_window(title, size)}
		{
			glfwSetWindowUserPointer(win.get(), events.get());

			// event dispatching
			glfwSetWindowCloseCallback(win.get(), [](auto win) {
				glfwSetWindowShouldClose(win, false);
				safe_call(events_from_window(win).close);
			});
		}

		void window::vsync(bool on)
		{
			meta::bind<window> _(*this);
			glfwSwapInterval(static_cast<int>(on));
		}
	}

	void bind_traits<window>::bind(value_type const& x)
	{
		glfwMakeContextCurrent(x);
	};

#ifndef RELEASE
	void bind_traits<window>::unbind(value_type const&)
	{
		glfwMakeContextCurrent({});
	};
#endif
}

