#pragma once

#include <iterator>

#include "lrl/functional/functional.hpp"

namespace lrl
{
	namespace iterators
	{
		template <typename T>
		struct begin_iterator
		{
			template <typename Container>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(Container&& container)
			{
				return (std::begin(std::forward<Container>(container)));
			}
		};

		template <typename T>
		struct end_iterator
		{
			template <typename Container>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(Container&& container)
			{
				return (std::end(std::forward<Container>(container)));
			}
		};

#if __cplusplus >= 201703L

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
