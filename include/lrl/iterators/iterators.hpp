#pragma once

#include <iterator>

namespace lrl
{
	namespace iterators
	{
#if __cplusplus >= 201402L

		template <typename T>
		struct begin_iterator
		{
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr static decltype(auto) begin(T&& container)
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
			constexpr static decltype(auto) end(T&& container)
			{
				return (std::end(std::forward<T>(container)));
			}
		};

		template <typename T>
#if __cplusplus >= 201703L
		[[nodiscard]]
#endif
		constexpr decltype(auto) begin(T&& container)
		{
			return (begin_iterator<T>::begin(std::forward<T>(container)));
		}

		template <typename T>
#if __cplusplus >= 201703L
		[[nodiscard]]
#endif
		constexpr decltype(auto) end(T&& container)
		{
			return (end_iterator<T>::end(std::forward<T>(container)));
		}

#endif
	}
}
