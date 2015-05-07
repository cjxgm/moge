#pragma once
#include "meta/constraints.hh"

namespace moge
{
	namespace system_detail
	{
		struct system : meta::singleton<system>
		{
			static void run(system& = instance());
			static void quit(system& = instance());
			static void update(system& = instance());

		private:
			system();
			~system();
			friend singleton;
		};
	}

	using system_detail::system;
}

