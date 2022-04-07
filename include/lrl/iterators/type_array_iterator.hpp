#pragma once

#include "lrl/iterators/index_iterator.hpp"
#include "lrl/containers/type_array.hpp"

namespace lrl
{
	namespace iterators
	{
		template <std::size_t Index, typename Tuple>
		using type_array_iterator = index_iterator<Index, Tuple>;

		template <typename ...Args>
		struct begin_iterator<lrl::containers::type_array<Args...>>
		{
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(const lrl::containers::type_array<Args...>& typeArray)
			{
				return 
				(
					type_array_iterator<0, lrl::containers::type_array<Args...>>
					{
						typeArray
					}
				);
			}
		};

		template <typename ...Args>
		struct end_iterator<lrl::containers::type_array<Args...>>
		{
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(const lrl::containers::type_array<Args...>& typeArray)
			{
				return 
				(
					type_array_iterator<lrl::containers::type_array<Args...>::size(), lrl::containers::type_array<Args...>>
					{
						typeArray
					}
				);
			}
		};
	}
}
