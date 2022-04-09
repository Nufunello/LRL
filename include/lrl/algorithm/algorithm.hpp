#pragma once

#include <algorithm>

#include "lrl/functional/functional.hpp"

namespace lrl
{
	namespace algorithm
	{
#if __cplusplus >= 201703L

		template <typename Begin, typename End, typename Callable>
		struct for_each_algorithm
		{
			template <typename B, typename E, typename C>
			constexpr decltype(auto) operator()(B&& begin, E&& end, C&& functor)
			{
				return 
				(
					std::for_each
					(
						std::forward<B>(begin), 
						std::forward<E>(end),
						std::forward<C>(functor)
					)
				);
			}
		};

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

		template <typename Begin, typename End, typename Predicate>
		struct find_if_algorithm
		{
			template <typename B, typename E, typename P>
			constexpr decltype(auto) operator()(B&& begin, E&& end, P&& functor)
			{
				return 
				(
					std::find_if
					(
						std::forward<B>(begin), 
						std::forward<E>(end),
						std::forward<P>(functor)
					)
				);
			}
		};

		template <template <typename, typename, typename> typename  FindIfFunctor = find_if_algorithm, typename Begin, typename End, typename Predicate>
		constexpr decltype(auto) find_if(Begin&& begin, End&& end, Predicate&& functor)
		{
			return 
			(
				functional::invoke_template_functor<FindIfFunctor>
				(
					std::forward<Begin>(begin), 
					std::forward<End>(end),
					std::forward<Predicate>(functor)
				)
			);
		}

		template <typename Begin, typename End, typename Predicate>
		struct remove_if_algorithm
		{
			template <typename B, typename E, typename P>
			constexpr decltype(auto) operator()(B&& begin, E&& end, P&& functor)
			{
				return 
				(
					std::remove_if
					(
						std::forward<B>(begin), 
						std::forward<E>(end),
						std::forward<P>(functor)
					)
				);
			}
		};

		template <template <typename, typename, typename> typename  RemoveIfFunctor = remove_if_algorithm, typename Begin, typename End, typename Predicate>
		constexpr decltype(auto) remove_if(Begin&& begin, End&& end, Predicate&& functor)
		{
			return 
			(
				functional::invoke_template_functor<RemoveIfFunctor>
				(
					std::forward<Begin>(begin), 
					std::forward<End>(end),
					std::forward<Predicate>(functor)
				)
			);
		}

#endif
	}
}
