#pragma once
#include "bind-traits.hh"
#include "constraints.hh"
#include <utility>		// for std::move
#include <stdexcept>
#include <cstddef>		// for std::size_t

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
			if (nbound && value != x) throw failure{"multiple bind"};
			if (nbound++) return;
			value = x;
			traits::bind(value);
		}

		~bind()
		{
			if (--nbound) return;
			traits::unbind(value);
		}

	private:
		static thread_local std::size_t nbound;
		static thread_local value_type value;

		struct failure : std::logic_error { using logic_error::logic_error; };
	};

	template <class TAG>
	thread_local std::size_t
	bind<TAG>::nbound{};

	template <class TAG>
	thread_local typename bind<TAG>::value_type
	bind<TAG>::value;
}

