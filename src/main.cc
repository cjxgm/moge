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
}

int main()
{
	window win1;
	win1.bind();

	array_buffer buf;
	buf.bind();
	float points[] = {
		-0.5, -0.5,
		+0.3, +0.4,
	};
	buf.data(buffer_usage::static_draw, points, sizeof(points));

	vertex_array arr;
	arr.bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

	auto p1 = load_program(win1);

	optional<window> win2;
	win2 = window{"window 2", {320, 240}};
	win2->events->close = [&] { win2 = {}; };

	auto p2 = load_program(*win2);

	auto& sys = system::instance();
	while (sys.poll()) {
		{
			auto w_ = win1.bind();
			auto p_ = p1.bind();
			clear_color({1, 1, 1, 1});
			clear(clear_target::color_buffer);
			arr.draw_point(2);
			win1.update();
		}

		if (win2) {
			auto& win = *win2;
			auto w_ = win.bind();
			auto p_ = p2.bind();
			clear_color({1, 0, 0, 1});
			clear(clear_target::color_buffer);
			win.update();
		}
	}
}

