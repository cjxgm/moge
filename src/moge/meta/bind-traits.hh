#pragma once

namespace moge
{
	namespace meta
	{
		template <class TAG>
		struct bind_traits;
		/*
		{
			using value_type = VALUE_TYPE;
			static constexpr value_type nil() { return {}; }
			static void bind(value_type const& x) { do_bind(x); }
		}
		*/

		template <class T>
		struct make_bind_traits
		{
			using value_type = T;
			static constexpr value_type nil() { return {}; }
			// write yourself: static void bind(value_type const& x);
		};
	}

	using meta::bind_traits;
	using meta::make_bind_traits;
}

