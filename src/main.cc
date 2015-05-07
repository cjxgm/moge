#include "moge/system.hh"
#include "moge/window.hh"
#include "moge/meta/bind.hh"
#include "moge/meta/optional.hh"

int main()
{
	moge::window win;
	win.vsync();
	win.events->close = [] { moge::system::quit(); };

	meta::optional<moge::window> win2;
	win2 = moge::window{"window 2", {320, 240}};
	win2->vsync();
	win2->events->close = [&] { win2 = {}; };

	moge::system::run();
}

