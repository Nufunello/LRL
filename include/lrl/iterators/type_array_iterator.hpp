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
			template <typename TypeArray>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(TypeArray&& typeArray)
			{
				return 
				(
					type_array_iterator<0, TypeArray>
					{
						std::forward<TypeArray>(typeArray)
					}
				);
			}
		};

		template <typename ...Args>
		struct end_iterator<lrl::containers::type_array<Args...>>
		{
			template <typename TypeArray>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(TypeArray&& typeArray)
			{
				return 
				(
					type_array_iterator<lrl::containers::type_array<Args...>::size(), TypeArray>
					{
						std::forward<TypeArray>(typeArray)
					}
				);
			}
		};
	}
}
