#pragma once
#include "gl.hh"
#include "gl-traits.hh"
#include <cstdint>
#include <tuple>

namespace moge
{
	namespace vertex_layout_detail
	{
		template <std::size_t DISTANCE> struct skip_index {};
		template <std::size_t     SIZE> struct padding    {};


		template <std::size_t I, class T> constexpr auto next_index = I+1;
		template <std::size_t I, std::size_t D> constexpr auto next_index<I, skip_index<D>> = I+D;
		template <std::size_t I, std::size_t S> constexpr auto next_index<I,    padding<S>> = I;


		template <class T> constexpr auto size_of = sizeof(T);
		template <std::size_t D> constexpr auto size_of<skip_index<D>> = 0;
		template <std::size_t S> constexpr auto size_of<   padding<S>> = S;


		namespace stride_detail
		{
			template <int X, int ...XS> constexpr auto sum = X;
			template <int Y, int X, int ...XS> constexpr auto sum<Y, X, XS...> = Y + sum<X, XS...>;
			template <class ...TS> constexpr auto stride = sum<size_of<TS>...>;
		}
		using stride_detail::stride;


		template <class ...TS>
		using make_padding = padding<stride<TS...>>;




		// prototype
		template <
			std::size_t I,
			GLsizei STRIDE,
			std::size_t OFFSET,
			class ...TS
		>
		struct vertex_layout;


		// base cases
		template <
			std::size_t I,
			GLsizei STRIDE,
			std::size_t OFFSET,
			class U
		>
		struct vertex_layout<I, STRIDE, OFFSET, U>
		{
			using traits = gl_traits<U>;

			static void apply()
			{
				glEnableVertexAttribArray(I);
				glVertexAttribPointer(I,
						traits::ncomponent,
						traits::type_enum,
						traits::normalize,
						STRIDE, reinterpret_cast<void const*>(OFFSET));
			}
		};

		template <
			std::size_t I,
			GLsizei STRIDE,
			std::size_t OFFSET,
			std::size_t D
		>
		struct vertex_layout<I, STRIDE, OFFSET, skip_index<D>>
		{
			static void apply() {}
		};

		template <
			std::size_t I,
			GLsizei STRIDE,
			std::size_t OFFSET,
			std::size_t S
		>
		struct vertex_layout<I, STRIDE, OFFSET, padding<S>>
		{
			static void apply() {}
		};


		// progression rule
		template <
			std::size_t I,
			GLsizei STRIDE,
			std::size_t OFFSET,
			class U,
			class T, class ...TS
		>
		struct vertex_layout<I, STRIDE, OFFSET, U, T, TS...>
		{
			using first = vertex_layout<I, STRIDE, OFFSET, U>;
			using rest  = vertex_layout<next_index<I, U>, STRIDE, OFFSET+size_of<U>, T, TS...>;

			static void apply()
			{
				first::apply();
				rest ::apply();
			}
		};
	}

	using vertex_layout_detail::skip_index;
	using vertex_layout_detail::padding;
	using vertex_layout_detail::make_padding;


	template <class ...TS, std::size_t I=0>
	void vertex_layout()
	{
		constexpr auto stride = vertex_layout_detail::stride<TS...>;
		using vl = vertex_layout_detail::vertex_layout<I, stride, 0, TS...>;
		vl::apply();
	}
}

