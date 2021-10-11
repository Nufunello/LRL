#pragma once

#include <algorithm>

#include "lrl/functional/functional.hpp"

namespace lrl
{
	namespace algorithm
	{
		template <typename Begin, typename End, typename Callable>
		struct for_each_algorithm
		{
			constexpr decltype(auto) operator()(Begin&& begin, End&& end, Callable&& functor)
			{
				return 
				(
					std::for_each
					(
						std::forward<Begin>(begin), 
						std::forward<End>(end),
						std::forward<Callable>(functor)
					)
				);
			}
		};

#if __cplusplus >= 201703L

		template <template <typename, typename, typename> typename  ForeachFunctor = for_each_algorithm, typename Begin, typename End, typename Callable>
		constexpr decltype(auto) for_each(Begin&& begin, End&& end, Callable&& functor)
		{
			return 
			(
				functional::invoke_template_functor<ForeachFunctor>
				(
					std::forward<Begin>(begin), 
					std::forward<End>(end),
					std::forward<Callable>(functor)
				)
			);
		}

#endif
	}
}
