#include "moge/system.hh"
#include "moge/window.hh"
#include "moge/meta/optional.hh"
#include "moge/meta/bind.hh"
#include "moge/misc.hh"
#include "moge/steady-updater.hh"
#include "moge/shader.hh"
#include "moge/program.hh"
#include "moge/utils.hh"
using namespace moge;

#include <iostream>
using std::cerr;

int main()
{
	window win1{"hello world"};
	{
		bind<window> _{win1};
		program p{
			vertex_shader{load_file("shader/main/vertex")},
			geometry_shader{load_file("shader/main/geometry")},
			fragment_shader{load_file("shader/main/fragment")},
		};
	}

	optional<window> win2;
	win2 = window{"window 2", {320, 240}};
	win2->events->close = [&] { win2 = {}; };

	auto& sys = system::instance();
	steady_updater<30> sup;
	while (sys.poll()) {
		cerr << "frame\n";
		sup();
		while (sup) cerr << "update\n";

		{
			bind<window> _(win1);
			moge::clear_color({1, 1, 1, 1});
			moge::clear(moge::clear_mask::color);
			win1.update();
		}

		if (win2) {
			auto& win = *win2;
			bind<window> _(win);
			moge::clear_color({1, 0, 0, 1});
			moge::clear(moge::clear_mask::color);
			win.update();
		}
	}
}

