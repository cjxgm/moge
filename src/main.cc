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

namespace
{
	auto load_program(window const& win)
	{
		bind<window> _{win};
		return program{
			vertex_shader{load_file("shader/main/vertex")},
			geometry_shader{load_file("shader/main/geometry")},
			fragment_shader{load_file("shader/main/fragment")},
		};
	}
}

int main()
{
	window win1{"hello world"};

	optional<window> win2;
	win2 = window{"window 2", {320, 240}};
	win2->events->close = [&] { win2 = {}; };

	auto p1 = load_program(win1);
	auto p2 = load_program(*win2);

	auto& sys = system::instance();
	while (sys.poll()) {
		{
			bind<window> _(win1);
			bind<program> __(p1);
			moge::clear_color({1, 1, 1, 1});
			moge::clear(moge::clear_mask::color);
			win1.update();
		}

		if (win2) {
			auto& win = *win2;
			bind<window> _(win);
			bind<program> __(p2);
			moge::clear_color({1, 0, 0, 1});
			moge::clear(moge::clear_mask::color);
			win.update();
		}
	}
}

