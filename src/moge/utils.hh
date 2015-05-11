#pragma once
#include <utility>		// for std::forward
#include <string>

namespace moge
{
	namespace utils
	{
		template <class F, class ...ARGS>
		void safe_call(F const& f, ARGS &&... args)
		{
			if (f) f(std::forward<ARGS>(args)...);
		}

		std::string load_file(std::string const& path);
	}

	using utils::safe_call;
	using utils::load_file;
}

