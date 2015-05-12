#pragma once
#include "resource-traits.hh"
#include "constraints.hh"
#include <stdexcept>
#include <cstddef>		// for std::size_t

namespace moge
{
	namespace meta
	{
		template <class TAG>
		struct bind : only_movable
		{
			using tag = TAG;
			using traits = resource_traits<tag>;
			using value_type = typename traits::value_type;

			static constexpr auto nil() { return traits::nil(); }

			// TODO: split reference counting to a separate construct
			bind(value_type const& x=nil())
			{
				if (traits::bound() == x) goto count_reference;
				if (nbound) throw violated{"multiple bind"};
				traits::bind(x);

			count_reference:
				nbound++;
			}

			bind(bind &&) { nbound++; }
			bind& operator = (bind &&) { nbound++; return *this; }

			~bind() { --nbound; }

		private:
			static thread_local std::size_t nbound;

			struct violated : std::logic_error { using logic_error::logic_error; };
		};

		template <class TAG>
		thread_local std::size_t bind<TAG>::nbound{};
	}

	using meta::bind;
}

