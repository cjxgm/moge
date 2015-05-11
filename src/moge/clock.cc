#include "clock.hh"
#include <chrono>

namespace moge
{
	namespace clock_detail
	{
		namespace
		{
			using c = std::chrono::high_resolution_clock;
			using ns = std::chrono::nanoseconds;
			using std::chrono::duration_cast;
		}

		auto clock::now() -> time_point
		{
			static auto epoch = c::now();
			return duration_cast<ns>(c::now() - epoch).count() * 1e-9f;
		}
	}
}

