#pragma once

namespace moge
{
	namespace clock_detail
	{
		struct clock
		{
			using time_point = float;
			using duration   = float;

			static time_point now();

			clock() : start{now()} {}
			void advance(duration d) { start += d; }
			void reset() { start = now(); }

			// you must freeze() before read() !
			void freeze() { freeze_point = now(); }
			duration read() const { return freeze_point - start; }

			auto& operator += (duration d) { advance(d); return *this; }
			operator auto () const { return read(); }

		private:
			time_point start;
			time_point freeze_point;
		};
	}

	using clock_detail::clock;
}

