#pragma once

#include <cstddef>
#include <type_traits>

#include "lrl/functional/functional.hpp"

namespace lrl
{
	namespace containers
	{
		template <typename IntegralConstant, typename T>
		struct getter
		{
			template <std::size_t Index, typename Container>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(const std::integral_constant<std::size_t, Index>&, Container&& container)
			{
				return (std::get<Index>(std::forward<Container>(container)));
			}
		};

		template <std::size_t Index, template <typename...> typename GetterFunctor = getter, typename T>
#if __cplusplus >= 201703L
		[[nodiscard]]
#endif
		constexpr decltype(auto) get(T&& container)
		{
			return (functional::invoke_template_functor<GetterFunctor>(
				std::integral_constant<std::size_t, Index>{}, std::forward<T>(container)));
		}
	}
}
