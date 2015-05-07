#include "system.hh"
#include "exceptions.hh"
#include <GLFW/glfw3.h>

namespace moge
{
	namespace system_detail
	{
		namespace
		{
			bool should_quit;
		}

		system::system()
		{
			should_quit = false;
			glfwSetErrorCallback([](auto, auto msg) { throw system_failure{msg}; });
			if (!glfwInit()) throw system_failure{"glfw-init"};
		}

		system::~system()
		{
			glfwTerminate();
		}

		void system::run(system&)
		{
			while (!should_quit) {
				glfwWaitEvents();
				// TODO: on_update event
			}
		}

		void system::quit(system& sys)
		{
			should_quit = true;
			update(sys);
		}

		void system::update(system&)
		{
			glfwPostEmptyEvent();
		}
	}
}

