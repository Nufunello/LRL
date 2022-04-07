#pragma once

#include <functional>
#include  <type_traits>

namespace lrl
{
	namespace functional
	{
#if __cplusplus >= 201703L

		template <typename Functor, typename... Args>
		constexpr decltype(auto) invoke(Functor&& functor, Args&& ...arguments)
		{
			return functor(std::forward<Args>(arguments)...);
		}
		template <typename Class, typename Type>
		constexpr decltype(auto) invoke(Type (Class::*member), Class& object)
		{
			return (object.*member);
		}
		template <typename Class, typename Type>
		constexpr decltype(auto) invoke(Type (Class::*member), const Class& object)
		{
			return (object.*member);
		}
		template <typename Class, typename Type, typename... Args, typename... Argss>
		constexpr decltype(auto) invoke(Type (Class::*method)(Args...), Class& object, Argss&& ...args)
		{
			return (object.*method)(std::forward<Argss>(args)...);
		}
		template <typename Class, typename Type, typename... Args, typename... Argss>
		constexpr decltype(auto) invoke(Type (Class::*method)(Args...) const, const Class& object, Argss&& ...args)
		{
			return (object.*method)(std::forward<Argss>(args)...);
		}

		template <template <typename...> typename Functor, typename... Args>
		constexpr decltype(auto) invoke_template_functor(Args&& ...arguments)
		{
			return 
			(
				Functor<std::decay_t<Args>...>{}(std::forward<Args>(arguments)...)
			);
		}

#endif
	}
}
