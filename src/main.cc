#include "moge/system.hh"
#include "moge/window.hh"
#include "moge/meta/optional.hh"
#include "moge/meta/bind.hh"
#include "moge/misc.hh"
#include "moge/steady-updater.hh"
#include "moge/shader.hh"
#include "moge/program.hh"
#include "moge/uniform-variable.hh"
#include "moge/utils.hh"
#include "moge/vertex-array.hh"
#include "moge/vertex-layout.hh"
#include "moge/buffer.hh"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <array>
#include <type_traits>
#include <utility>		// for std::forward
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

	struct vertex
	{
		glm::vec2 pos;
		glm::vec3 color;
		static void layout()
		{
			vertex_layout<
				glm::vec2,
				glm::vec3
			>();
		}
	};

	vertex const points[] = {
		{{ -0.5, -0.5 }, { 0, 1, 0 }},
		{{ +0.3, +0.4 }, { 0, 0, 1 }},
	};
	constexpr auto npoint = sizeof(points)/sizeof(points[0]);

	auto load_buffer(window const& win)
	{
		auto _ = win.bind();
		array_buffer buf;
		buf.bind();
		buf.data(buffer_usage::static_draw, points, sizeof(points));
		return buf;
	}

	auto load_array(window const& win)
	{
		auto _ = win.bind();
		vertex_array arr;
		arr.bind();
		vertex::layout();
		return arr;
	}
}

int main()
{
	window win1;
	auto buf1 = load_buffer (win1);
	auto arr1 = load_array  (win1);
	auto pro1 = load_program(win1);
	pro1.bind();
	uniform_variable<float> time1{pro1, "time"};
	uniform_variable<glm::vec2> off1{pro1, "off"};

	optional<window> win2;
	win2 = window{"window 2", {320, 240}};
	win2->events->close = [&] { win2 = {}; };

	auto buf2 = load_buffer (*win2);
	auto arr2 = load_array  (*win2);
	auto pro2 = load_program(*win2);
	pro2.bind();
	uniform_variable<float> time2{pro2, "time"};

	auto& sys = system::instance();
	while (sys.poll()) {
		{
			auto _ = win1.bind();
			clear_color({1, 1, 1, 1});
			clear(clear_target::color_buffer);
			time1 = clock::now();
			off1 = glm::vec2{0.5, 0.5};
			arr1.draw_point(npoint);
			win1.update();
		}

		if (win2) {
			auto _ = win2->bind();
			clear_color({1, 0, 0, 1});
			clear(clear_target::color_buffer);
			time2 = -clock::now();
			arr2.draw_point(npoint);
			win2->update();
		}
	}
}

