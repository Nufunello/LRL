#include "gtest/gtest.h"

#include "lrl/containers/type_array.hpp"

TEST(functional, type_array)
{
	const lrl::containers::type_array<int, float, double, char, char*> array;
	ASSERT_EQ(lrl::containers::get<0>(array), lrl::containers::type<int>{});
	ASSERT_EQ(lrl::containers::get<2>(array), lrl::containers::type<double>{});
	ASSERT_EQ(lrl::containers::get<4>(array), lrl::containers::type<char*>{});
}
