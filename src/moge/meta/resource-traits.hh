#pragma once

namespace moge
{
	namespace meta
	{
		template <class TAG>
		struct resource_traits;
		/*
		{
			using value_type = VALUE_TYPE;
			static constexpr value_type nil() { return {}; }
			static value_type allocate() { return do_allocate(); }
			static void deallocate(value_type const& x) { return do_deallocate(x); }
		}
		*/

		template <class T>
		struct make_resource_traits
		{
			using value_type = T;
			static constexpr value_type nil() { return {}; }
			// write yourself: static value_type allocate() { return do_allocate(); }
			// write yourself: static void deallocate(value_type const& x) { return do_deallocate(x); }
		};
	}

	using meta::resource_traits;
	using meta::make_resource_traits;
}

