#include "window.hh"
#include "system.hh"
#include "exceptions.hh"
#include "meta/bind.hh"
#include "utils.hh"
#include "misc.hh"
#include <GLFW/glfw3.h>
#include <utility>		// for std::forward

namespace moge
{
	namespace window_detail
	{
		namespace
		{
			auto make_window(std::string const& title, glm::ivec2 const& size)
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

				auto win = glfwCreateWindow(size.x, size.y, title.c_str(), {}, {});
				if (!win) throw window_failure{"glfw-create-window"};
				return win;
			}

			auto& events_from_window(GLFWwindow* win)
			{
				auto up = glfwGetWindowUserPointer(win);
				auto ev = reinterpret_cast<window_events*>(up);
				return *ev;
			}
		}

		window::window(std::string const& title,
				glm::vec2 const& size,
				system& sys)
			: resource{make_window(title, size)}
			, events{std::make_unique<window_events>()}
		{
			events->close = [&] { sys.quit(); };
			glfwSetWindowUserPointer(*this, events.get());

			// event dispatching
			glfwSetWindowCloseCallback(*this, [](auto win) {
				glfwSetWindowShouldClose(win, false);
				safe_call(events_from_window(win).close);
			});
			glfwSetWindowSizeCallback(*this, [](auto win, auto w, auto h) {
				auto& resize = events_from_window(win).resize;
				if (resize) resize({w, h});
				else {
					meta::bind<window> _{win};
					viewport({w, h});
				}
			});
		}

		void window::vsync(bool on)
		{
			bind();
			glfwSwapInterval(static_cast<int>(on));
		}

		void window::update()
		{
			bind();
			glfwSwapBuffers(*this);
		}
	}


	void resource_traits<window>::deallocate(value_type const& x)
	{
		glfwDestroyWindow(x);
	};

	void resource_traits<window>::bind(value_type const& x)
	{
		glfwMakeContextCurrent(x);
	}

	auto resource_traits<window>::bound() -> value_type
	{
		return glfwGetCurrentContext();
	}
}

