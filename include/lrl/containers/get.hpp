#pragma once

#include <cstddef>
#include <type_traits>

namespace lrl
{
	namespace containers
	{
		template <std::size_t Index>
		struct getter_index
		{
			template <typename T>
			struct getter_type
			{
				template <typename Container>
#if __cplusplus >= 201703L
				[[nodiscard]]
#endif
				constexpr decltype(auto) operator()(Container&& container)
				{
					return (std::get<Index>(std::forward<Container>(container)));
				}
			};
		};

#if __cplusplus >= 201703L

		template <std::size_t Index, template <typename> typename GetterFunctor = getter_index<Index>::template getter_type, typename T>
#if __cplusplus >= 201703L
		[[nodiscard]]
#endif
		constexpr decltype(auto) get(T&& container)
		{
			return (functional::invoke_template_functor<GetterFunctor>(std::forward<T>(container)));
		}

#endif
	}
}
