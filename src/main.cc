#include "moge/system.hh"
#include "moge/window.hh"
#include "moge/meta/optional.hh"
#include "moge/meta/bind.hh"
#include "moge/misc.hh"
#include "moge/steady-updater.hh"
#include "moge/shader.hh"
#include "moge/program.hh"
#include "moge/utils.hh"
#include "moge/vertex_array.hh"
#include "moge/buffer.hh"
using namespace moge;

namespace
{
	auto load_program(window const& win)
	{
		auto _ = win.bind();
		return program{
			vertex_shader{load_file("shader/main/vertex")},
			geometry_shader{load_file("shader/main/geometry")},
			fragment_shader{load_file("shader/main/fragment")},
		};
	}

	auto load_buffer(window const& win)
	{
		auto _ = win.bind();
		array_buffer buf;
		buf.bind();
		static float const points[] = {
			-0.5, -0.5,
			+0.3, +0.4,
		};
		buf.data(buffer_usage::static_draw, points, sizeof(points));
		return buf;
	}

	auto load_array(window const& win)
	{
		auto _ = win.bind();
		vertex_array arr;
		arr.bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
		return arr;
	}
}

int main()
{
	window win1;
	win1.bind();
	auto buf1 = load_buffer (win1);
	auto arr1 = load_array  (win1);
	auto pro1 = load_program(win1);
	pro1.bind();

	optional<window> win2;
	win2 = window{"window 2", {320, 240}};
	win2->events->close = [&] { win2 = {}; };

	win2->bind();
	auto buf2 = load_buffer (*win2);
	auto arr2 = load_array  (*win2);
	auto pro2 = load_program(*win2);
	pro2.bind();

	auto& sys = system::instance();
	while (sys.poll()) {
		{
			win1.bind();
			clear_color({1, 1, 1, 1});
			clear(clear_target::color_buffer);
			arr1.draw_point(2);
			win1.update();
		}

		if (win2) {
			win2->bind();
			clear_color({1, 0, 0, 1});
			clear(clear_target::color_buffer);
			arr2.draw_point(2);
			win2->update();
		}
	}
}

