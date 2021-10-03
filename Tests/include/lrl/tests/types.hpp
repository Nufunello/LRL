#pragma once

#include <type_traits>

namespace lrl_tests
{
	namespace types
	{
		template<typename Lambda1, typename Lambda2, typename ...Types>
		constexpr bool areInvokeResultsTypeSame()
		{
			return (std::is_same_v<
				std::invoke_result_t<Lambda1, Types>,
				std::invoke_result_t<Lambda2, Types>>
				&&
				...
			) && sizeof...(Types) > 0;
		}

		template<typename InvokeType, typename Lambda1, typename Lambda2>
		constexpr bool isInvokeResultTypeSame(Lambda1&&, Lambda2&&)
		{
			using rvalue = std::add_rvalue_reference_t<InvokeType>;
			using lvalue = std::add_lvalue_reference_t<InvokeType>;
			using const_lvalue = std::add_const_t<lvalue>;
			return areInvokeResultsTypeSame<Lambda1, Lambda2, InvokeType, rvalue, lvalue, const_lvalue>();
		}
	}
}
