#pragma once
#include "meta/constraints.hh"
#include <functional>

namespace moge
{
	namespace system_detail
	{
		struct system_events
		{
			using update_func = std::function<void ()>;
			using render_func = std::function<void ()>;

			float update_step{1.0f / 60.0f};	// seconds per update, 60 updates per second by default
			update_func update;
			render_func render;
		};

		struct system : meta::singleton<system>
		{
			static void run(system& = instance());
			static void quit(system& = instance());
			static void update(system& = instance());

			static system_events events;

		private:
			system();
			~system();
			friend singleton;
		};
	}

	using system_detail::system;
}

