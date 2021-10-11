#include <vector>

#include "gtest/gtest.h"

#include "lrl_tests/types.hpp"
#include "lrl/iterators/iterators.hpp"

TEST(iterators, EndReturn)
{
	using vector_type = std::vector<int>;
	constexpr bool endSameType = lrl_tests::types::isInvokeResultTypeSame<vector_type>
	(
		  [](auto&& vec){ return (std::end(std::forward<decltype(vec)>(vec))); }
		, [](auto&& vec){ return (lrl::iterators::end(std::forward<decltype(vec)>(vec))); }
	);
	EXPECT_TRUE(endSameType)
		<< "calls of functions \"end\" should return same type";
	const vector_type vector = {1, 2, 3, 4, 5, 6};
	EXPECT_EQ(std::end(vector), lrl::iterators::end(vector))
		<< "calls of functions \"end\" are not equal for vector";
}
