#include "moge/system.hh"
#include "moge/window.hh"
#include "moge/meta/optional.hh"
#include "moge/meta/bind.hh"
#include "moge/gl.hh"
using namespace moge;

int main()
{
	window win1{"hello world"};

	optional<window> win2;
	win2 = window{"window 2", {320, 240}};
	win2->events->close = [&] { win2 = {}; };

	system::events.render = [&] {
		{
			bind<window> _(win1);
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			win1.update();
		}

		if (win2) {
			auto& win = *win2;
			bind<window> _(win);
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			win.update();
		}
	};

	system::run();
}

