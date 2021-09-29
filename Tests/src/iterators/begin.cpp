#include <vector>

#include "gtest/gtest.h"

#include "lrl/tests/types.hpp"
#include "lrl/iterators/iterators.hpp"

TEST(iterators, BeginReturn)
{
	using vector_type = std::vector<int>;
	constexpr bool beginSameType = lrl::tests::types::isInvokeResultTypeSame<vector_type>
	(
		  [](auto&& vec){ return (std::begin(std::forward<decltype(vec)>(vec))); }
		, [](auto&& vec){ return (lrl::iterators::begin(std::forward<decltype(vec)>(vec))); }
	);
	EXPECT_TRUE(beginSameType)
		<< "calls of functions \"begin\" should return same type";
	const vector_type vector = {1, 2, 3, 4, 5, 6};
	EXPECT_EQ(std::begin(vector), lrl::iterators::begin(vector)) 
		<< "calls of functions \"begin\" are not equal for vector";	
}
