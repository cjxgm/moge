#pragma once
#include <utility>		// for std::forward

namespace moge
{
	namespace utils
	{
		template <class F, class ...ARGS>
		void safe_call(F const& f, ARGS &&... args)
		{
			if (f) f(std::forward<ARGS>(args)...);
		}
	}

	using utils::safe_call;
}

