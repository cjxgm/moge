#include "system.hh"
#include "exceptions.hh"
#include "utils.hh"
#include <GLFW/glfw3.h>

namespace moge
{
	namespace system_detail
	{
		namespace
		{
			bool should_continue{true};
		}

		system::system()
		{
			glfwSetErrorCallback([](auto, auto msg) { throw system_failure{msg}; });
			if (!glfwInit()) throw system_failure{"glfw-init"};
		}

		system::~system()
		{
			glfwTerminate();
		}

		bool system::wait()
		{
			glfwWaitEvents();
			return should_continue;
		}

		bool system::poll()
		{
			glfwPollEvents();
			return should_continue;
		}

		void system::quit()
		{
			should_continue = false;
			update();
		}

		void system::update()
		{
			glfwPostEmptyEvent();
		}
	}
}

