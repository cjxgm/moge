#pragma once
#include "meta/constraints.hh"
#include <functional>

namespace moge
{
	namespace system_detail
	{
		struct system : meta::singleton<system>
		{
			void quit();
			bool wait();
			bool poll();
			void update();

		private:
			system();
			~system();
			friend singleton;
		};
	}

	using system_detail::system;
}

