#include "moge/system.hh"
#include "moge/window.hh"
#include "moge/meta/optional.hh"
using namespace moge;

int main()
{
	window win1{"hello world"};
	win1.vsync();
	win1.events->close = [] { system::quit(); };

	optional<window> win2;
	win2 = window{"window 2", {320, 240}};
	win2->events->close = [&] { win2 = {}; };

	system::run();
}

