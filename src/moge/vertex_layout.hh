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
			std::size_t I=0,
			GLsizei STRIDE=stride<U>,
			std::size_t OFFSET=0
		>
		void vertex_layout()
		{
			using traits = gl_traits<U>;
			glVertexAttribPointer(I,
					traits::ncomponent,
					traits::type_enum,
					traits::normalize,
					STRIDE, OFFSET);
		}

		template <
			class U,
			class T, class ...TS,
			std::size_t I=0,
			GLsizei STRIDE=stride<U, T, TS...>,
			std::size_t OFFSET=0
		>
		void vertex_layout()
		{
			vertex_layout<U, I, STRIDE, OFFSET>;
			vertex_layout<T, TS..., I+1, STRIDE, OFFSET+sizeof(U)>;
		}
	}
}

