#include <vector>
#include <type_traits>

#include "gtest/gtest.h"

#include "lrl/iterators/iterators.hpp"

namespace
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
	template<typename T, typename Lambda1, typename Lambda2>
	constexpr bool isInvokeResultTypeSame(Lambda1&&, Lambda2&&)
	{
		return areInvokeResultsTypeSame<Lambda1, Lambda2, 
			T, std::add_rvalue_reference_t<T>,
			std::add_const_t<std::add_lvalue_reference_t<T>>, std::add_lvalue_reference_t<T>>();
	}	
	class IteratorsBeginEnd 
		: public ::testing::Test 
	{	
	};	
	TEST_F(IteratorsBeginEnd, VectorIterators)
	{
		using vector_type = std::vector<int>;
		{
			constexpr bool beginSameType = isInvokeResultTypeSame<vector_type>(
				  [](auto&& vec){ return std::begin(vec); }
				, [](auto&& vec){ return lrl::iterators::begin(vec); }
			);
			EXPECT_TRUE(beginSameType)
				<< "calls of functions \"begin\" should return same type";
		}	
		{
			constexpr bool endSameType = isInvokeResultTypeSame<vector_type>(
				  [](auto&& vec){ return std::end(vec); }
				, [](auto&& vec){ return lrl::iterators::end(vec); }
			);
			EXPECT_TRUE(endSameType)
				<< "calls of functions \"end\" should return same type";
		}	
		const vector_type vector = {1, 2, 3, 4, 5, 6};
		EXPECT_EQ(std::begin(vector), lrl::iterators::begin(vector)) 
			<< "calls of functions \"begin\" are not equal for vector";	
		EXPECT_EQ(std::end(vector), lrl::iterators::end(vector))
			<< "calls of functions \"end\" are not equal for vector";
	}
}
