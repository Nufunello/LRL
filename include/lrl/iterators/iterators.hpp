#pragma once

#include <iterator>

#include "lrl/functional/functional.hpp"

namespace lrl
{
	namespace iterators
	{
#if __cplusplus >= 201703L

		template <typename T>
		struct begin_iterator
		{
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(T&& container)
			{
				return (std::begin(std::forward<T>(container)));
			}
		};

		template <typename T>
		struct end_iterator
		{
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(T&& container)
			{
				return (std::end(std::forward<T>(container)));
			}
		};

		template <template <typename> typename  BeginFunctor = begin_iterator, typename T>
#if __cplusplus >= 201703L
		[[nodiscard]]
#endif
		constexpr decltype(auto) begin(T&& container)
		{
			return (functional::invoke_template_functor<BeginFunctor>(std::forward<T>(container)));
		}

		template <template <typename> typename EndFunctor = end_iterator, typename T>
#if __cplusplus >= 201703L
		[[nodiscard]]
#endif
		constexpr decltype(auto) end(T&& container)
		{
			return (functional::invoke_template_functor<EndFunctor>(std::forward<T>(container)));
		}

#endif
	}
}
