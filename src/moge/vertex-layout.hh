#pragma once
#include "gl.hh"
#include "gl-traits.hh"
#include <cstdint>
#include <tuple>

namespace moge
{
	namespace vertex_layout_detail
	{
		template <class ...TS>
		constexpr auto stride = sizeof(std::tuple<TS...>);

		template <
			class U,
			std::size_t I,
			GLsizei STRIDE,
			std::size_t OFFSET
		>
		void vertex_layout()
		{
			using traits = gl_traits<U>;
			glEnableVertexAttribArray(I);
			glVertexAttribPointer(I,
					traits::ncomponent,
					traits::type_enum,
					traits::normalize,
					STRIDE, reinterpret_cast<void const*>(OFFSET));
		}

		template <
			class U,
			class T, class ...TS,
			std::size_t I,
			GLsizei STRIDE,
			std::size_t OFFSET
		>
		void vertex_layout()
		{
			vertex_layout<U, I, STRIDE, OFFSET>;
			vertex_layout<T, TS..., I+1, STRIDE, OFFSET+sizeof(U)>;
		}
	}

	template <class ...TS, std::size_t I=0>
	void vertex_layout()
	{
		constexpr auto stride = vertex_layout_detail::stride<TS...>;
		vertex_layout_detail::vertex_layout<TS..., I, stride, 0>();
	}
}

