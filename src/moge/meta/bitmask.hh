#include <type_traits>

namespace moge
{
	namespace meta
	{
		template <class TAG, class T>
		struct bitmask
		{
			using tag = TAG;
			using value_type = T;
			static_assert(std::is_integral<value_type>{},
					"value_type must be integral type!");

			constexpr bitmask() : bitmask{{}} {}
			explicit constexpr bitmask(value_type x) : value{x} {}

			constexpr auto get() const { return value; }
			explicit constexpr operator auto () const { return get(); }

		private:
			const value_type value;

			friend constexpr bitmask operator | (bitmask a, bitmask b)
			{
				return {a.value | b.value};
			}
		};
	}

	using meta::bitmask;
}

