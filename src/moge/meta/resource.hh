// an any-type resource with the same semantics of unique_ptr
#pragma once
#include "resource-traits.hh"
#include "constraints.hh"
#include <utility>		// for std::move

namespace moge
{
	namespace meta
	{
		struct nil_resource {};

		template <class TAG>
		struct resource : only_movable
		{
			using tag = TAG;
			using traits = resource_traits<tag>;
			using value_type = typename traits::value_type;

			static constexpr auto nil() { return traits::nil(); }


			//------ rule of three
			resource() : value{traits::allocate()} {}
			resource(resource && x) : value{x.release()} {}

			auto& operator = (resource && x) { reset(x.release()); return *this; }

			~resource() { if (value != nil()) traits::deallocate(value); }


			//------ accessors
			auto& get() const { return value; }
			operator auto& () const { return get(); }
			auto& operator * () const { return get(); }


			//------ modifiers
			void reset(value_type x=nil())
			{
				if (value != nil()) traits::deallocate(value);
				value = std::move(x);
			}

			auto release()
			{
				auto x = std::move(value);
				value = nil();
				return x;
			}

			auto& operator = (value_type x) { reset(std::move(x)); return *this; }


		private:
			value_type value;
		};
	}
}

