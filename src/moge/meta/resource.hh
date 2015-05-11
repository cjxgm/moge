// an any-type resource with the same semantics of unique_ptr
#pragma once
#include "resource-traits.hh"
#include "constraints.hh"
#include <utility>		// for std::move, std::swap
#include <stdexcept>

namespace moge
{
	namespace meta
	{
		template <class TAG>
		struct resource : only_movable
		{
			using tag = TAG;
			using traits = resource_traits<tag>;
			using value_type = typename traits::value_type;

			static constexpr auto nil() { return traits::nil(); }


			//------ life time
			resource() : resource{allocate()} {}
			resource(value_type x) : value{std::move(x)} {}
			resource(resource && x) : value{x.release()} {}
			~resource() { if (value != nil()) traits::deallocate(value); }


			//------ assignments
			auto& operator = (resource && x) { reset( x.release()); return *this; }
			auto& operator = (value_type  x) { reset(std::move(x)); return *this; }


			//------ accessors
			auto& get() const { return value; }
			operator auto& () const { return get(); }
			auto& operator * () const { return get(); }


			//------ modifiers
			void swap(resource & x) { std::swap(value, x.value); }
			void swap(resource && x) { std::swap(value, x.value); }
			void reset(value_type x=nil()) { swap({std::move(x)}); }
			auto release()
			{
				auto x = std::move(value);
				value = nil();
				return x;
			}


		private:
			value_type value;

			struct exausted : std::runtime_error { using runtime_error::runtime_error; };

			static auto allocate()
			{
				auto x = traits::allocate();
				if (x == nil()) throw exausted{"resource allocation failure"};
				return x;
			}
		};
	}

	using meta::resource;
}

