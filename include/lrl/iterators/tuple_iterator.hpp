#pragma once

#include <type_traits>

#include "lrl/iterators/iterators.hpp"

namespace lrl
{
	namespace iterators
	{
		template<size_t Index, typename Tuple>
		class tuple_iterator
		{
		public:
			constexpr tuple_iterator(Tuple tuple)
				: tuple{tuple}
			{}

#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator*()
			{
				return (std::get<Index>(tuple));
			}

#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator*() const
			{
				return (std::get<Index>(tuple));
			}
			
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr tuple_iterator<Index + 1, Tuple> operator++() const
			{
				return {tuple};
			}
			
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr tuple_iterator<Index + 1, Tuple> operator++(int) const
			{
				return {tuple};
			}
			
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr tuple_iterator<Index - 1, Tuple> operator--() const
			{
				return {tuple};
			}
			
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr tuple_iterator<Index - 1, Tuple> operator--(int) const
			{
				return {tuple};
			}

			template <size_t OtherIndex, typename OtherTuple>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr bool operator==(const tuple_iterator<OtherIndex, OtherTuple>&) const
			{
				return Index == OtherIndex 
					&& std::is_same_v
						<
							  std::decay_t<Tuple>
							, std::decay_t<OtherTuple>
						>;
			}

			template <size_t OtherIndex, typename OtherTuple>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr bool operator!=(const tuple_iterator<OtherIndex, OtherTuple>& other) const
			{
				return !(*this == other);
			}

		private:
			Tuple tuple;
		};

		template <size_t Index>
		struct boundary_tuple_iterator
		{
			template <typename Tuple>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(Tuple&& tuple)
			{
				return 
				(
					tuple_iterator<Index, Tuple>
					{
						std::forward<Tuple>(tuple)
					}
				);
			}
		};

		template <typename ...Args>
		struct begin_iterator<std::tuple<Args...>>
			: boundary_tuple_iterator<0>
		{};

		template <typename ...Args>
		struct end_iterator<std::tuple<Args...>>
			: boundary_tuple_iterator<std::tuple_size_v<std::tuple<Args...>>>
		{};
	}
}
