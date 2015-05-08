#pragma once
#include "bind-traits.hh"
#include "constraints.hh"
#include <stdexcept>
#include <cstddef>		// for std::size_t

namespace moge
{
	namespace meta
	{
		template <class TAG>
		struct bind : non_transferable
		{
			using tag = TAG;
			using traits = bind_traits<tag>;
			using value_type = typename traits::value_type;

			static constexpr auto nil() { return traits::nil(); }

			// TODO: split reference counting to a separate construct
			bind(value_type const& x=nil())
			{
				if (value == x) goto count_reference;
				if (nbound) throw violated{"multiple bind"};
				value = x;
				traits::bind(value);

			count_reference:
				nbound++;
			}

			~bind() { --nbound; }

		private:
			static thread_local std::size_t nbound;
			static thread_local value_type value;

			struct violated : std::logic_error { using logic_error::logic_error; };
		};

		template <class TAG>
		thread_local std::size_t
		bind<TAG>::nbound{};

		template <class TAG>
		thread_local typename bind<TAG>::value_type
		bind<TAG>::value;
	}

	using meta::bind;
}

