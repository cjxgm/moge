#pragma once
#include "clock.hh"

namespace moge
{
	namespace steady_updater_detail
	{
		template <int RATE>
		struct steady_updater
		{
			static constexpr auto rate() { return RATE; }
			static constexpr auto step() { return 1.0f / rate(); }

			bool should_update() const { return (clk > step()); }
			void mark_update() { clk += step(); }
			void pump() { clk.freeze(); }

			void operator () () { pump(); }
			operator bool ()
			{
				if (!should_update()) return false;
				mark_update();
				return true;
			}

		private:
			clock clk;
		};
	}

	using steady_updater_detail::steady_updater;
}

