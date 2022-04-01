#pragma once

#include "lrl/containers/get.hpp"

namespace lrl
{
	namespace containers
	{
		template <typename Type>
		class type
		{
		public:
			template <typename OtherType>
			constexpr auto operator==(const type<OtherType>&) const
				-> std::conditional_t<std::is_same_v<Type, OtherType>, std::true_type, std::false_type>
			{
				return {};
			}
		};

		template <typename ...Types>
		class type_array
		{
		public:
			constexpr static auto size()
			{
				return sizeof...(Types);
			}
		};

		template <typename IntegralConstant, typename ...Types>
		struct getter<IntegralConstant, type_array<Types...>>
		{
			template <std::size_t Index, typename Container>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator()(const std::integral_constant<std::size_t, Index>&, Container&&)
			{
				using Result = decltype(getByIndex<Index>(std::make_index_sequence<type_array<Types...>::size()>()));
				return typename Result::WithT<lrl::containers::type>{};
			}
		private:
			template <std::size_t Index, std::size_t... Indexes>
			constexpr static decltype(auto) getByIndex(const std::index_sequence<Indexes...>&)
			{
				return (TypeCollector<>{} + ... + TypeKey<Index == Indexes, Types>{});
			}

			template<bool Condition, typename Type>
			struct TypeKey{};

			template <typename... Type>
			struct TypeCollector
			{
				template <template <typename> typename T>
				using WithT = T<Type...>;

				template<bool Condition, typename T>
				constexpr auto operator+(TypeKey<Condition, T>) const
					-> std::conditional_t<Condition, TypeCollector<T>, TypeCollector<Type...>>
				{
					return {};
				}
			};
		};
	}
}
