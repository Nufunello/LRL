#pragma once

#include "lrl/iterators/index_iterator.hpp"

namespace lrl
{
	namespace iterators
	{
		template <std::size_t Index, typename Tuple>
		using tuple_iterator = index_iterator<Index, Tuple>;

		template <typename ...Args>
		struct begin_iterator<std::tuple<Args...>>
		{
			template <typename Tuple>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(Tuple&& tuple)
			{
				return 
				(
					tuple_iterator<0, Tuple>
					{
						std::forward<Tuple>(tuple)
					}
				);
			}
		};

		template <typename ...Args>
		struct end_iterator<std::tuple<Args...>>
		{
			template <typename Tuple>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(Tuple&& tuple)
			{
				return 
				(
					tuple_iterator<std::tuple_size_v<std::tuple<Args...>>, Tuple>
					{
						std::forward<Tuple>(tuple)
					}
				);
			}
		};
	}
}
