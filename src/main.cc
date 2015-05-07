#include "moge/system.hh"
#include "moge/window.hh"
#include "moge/meta/bind.hh"

int main()
{
	moge::window win;
	moge::window win2{"window 2", {320, 240}};
	meta::bind<moge::window> _(win);
	win.vsync();
	moge::system::run();
}

