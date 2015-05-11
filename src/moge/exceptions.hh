#pragma once
#include <stdexcept>

namespace moge
{
	inline namespace exceptions
	{
		using fatal_error = std::logic_error;
		struct system_failure : fatal_error { using fatal_error::fatal_error; };
		struct window_failure : fatal_error { using fatal_error::fatal_error; };
		struct shader_failure : fatal_error { using fatal_error::fatal_error; };
		struct program_failure: fatal_error { using fatal_error::fatal_error; };
	}
}

