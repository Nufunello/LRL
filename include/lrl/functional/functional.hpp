#pragma once

#include <functional>

namespace lrl
{
	namespace functional
	{
#if __cplusplus >= 201703L

		template <template <typename...> typename Functor, typename... Args>
		constexpr decltype(auto) invoke_template_functor(Args&& ...arguments)
		{
			return 
			(
				std::invoke(Functor<std::decay_t<Args>...>{}, 
				std::forward<Args>(arguments)...)
			);
		}

#endif
	}
}
