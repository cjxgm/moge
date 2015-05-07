#pragma once
#include "meta/constraints.hh"

namespace moge
{
	namespace system_detail
	{
		struct system : meta::singleton<system>
		{
			static void run();
			static void quit();

		private:
			system();
			~system();
			friend singleton;
		};
	}

	using system_detail::system;
}

