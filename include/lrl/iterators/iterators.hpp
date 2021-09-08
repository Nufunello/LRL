#pragma once

#include <functional>

namespace lrl
{
	namespace iterators
	{
#if __cplusplus >= 201402L //cpp 14

		template <typename T>
		struct begin_iterator
		{
			constexpr static decltype(auto) begin(T&& container)
			{
				return (std::begin(std::forward<T>(container)));
			}
		};

		template <typename T>
		struct end_iterator
		{
			constexpr static decltype(auto) end(T&& container)
			{
				return (std::end(std::forward<T>(container)));
			}
		};

		template <typename T>
		constexpr decltype(auto) begin(T&& container)
		{
			return (begin_iterator<T>::begin(std::forward<T>(container)));
		}

		template <typename T>
		constexpr decltype(auto) end(T&& container)
		{
			return (end_iterator<T>::end(std::forward<T>(container)));
		}

#endif
	}
}
