#pragma once
#include "bind-traits.hh"
#include "constraints.hh"
#include <utility>		// for std::move
#include <stdexcept>

namespace meta
{
	template <class TAG>
	struct bind : non_transferable
	{
		using tag = TAG;
		using traits = bind_traits<tag>;
		using value_type = typename traits::value_type;

		bind(value_type const& x)
		{
			if (bound && value == x) return;
			if (bound) throw failure{"multiple bind"};
			value = x;
			traits::bind(value);
			bound = true;
		}

		~bind()
		{
			if (!bound) return;
			traits::unbind(value);
			bound = false;
		}

	private:
		static thread_local bool bound;
		static thread_local value_type value;

		struct failure : std::logic_error { using logic_error::logic_error; };
	};

	template <class TAG>
	thread_local bool
	bind<TAG>::bound{false};

	template <class TAG>
	thread_local typename bind<TAG>::value_type
	bind<TAG>::value;
}

