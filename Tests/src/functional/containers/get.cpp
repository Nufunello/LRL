#include "gtest/gtest.h"

#include "lrl/containers/get.hpp"

TEST(functional, get_stl)
{
	{
		std::tuple container = {1.f, 2., "asdasd", 'a'};
		
		ASSERT_EQ(lrl::containers::get<0>(container), std::get<0>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<0>(container)), decltype(std::get<0>(container))>));
		
		ASSERT_EQ(lrl::containers::get<1>(container), std::get<1>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<1>(container)), decltype(std::get<1>(container))>));
		
		ASSERT_EQ(lrl::containers::get<2>(container), std::get<2>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<2>(container)), decltype(std::get<2>(container))>));
		
		ASSERT_EQ(lrl::containers::get<3>(container), std::get<3>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<3>(container)), decltype(std::get<3>(container))>));
	}
	{
		const std::tuple container = {1.f, 2., "asdasd", 'a'};

		ASSERT_EQ(lrl::containers::get<0>(container), std::get<0>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<0>(container)), decltype(std::get<0>(container))>));
		
		ASSERT_EQ(lrl::containers::get<1>(container), std::get<1>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<1>(container)), decltype(std::get<1>(container))>));
		
		ASSERT_EQ(lrl::containers::get<2>(container), std::get<2>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<2>(container)), decltype(std::get<2>(container))>));
		
		ASSERT_EQ(lrl::containers::get<3>(container), std::get<3>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<3>(container)), decltype(std::get<3>(container))>));
	}
	{
		std::pair container = {1.f, "asdasd"};

		ASSERT_EQ(lrl::containers::get<0>(container), std::get<0>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<0>(container)), decltype(std::get<0>(container))>));
		
		ASSERT_EQ(lrl::containers::get<1>(container), std::get<1>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<1>(container)), decltype(std::get<1>(container))>));
	}
	{
		const std::pair container = {1.f, "asdasd"};

		ASSERT_EQ(lrl::containers::get<0>(container), std::get<0>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<0>(container)), decltype(std::get<0>(container))>));
		
		ASSERT_EQ(lrl::containers::get<1>(container), std::get<1>(container));
		ASSERT_TRUE((std::is_same_v<decltype(lrl::containers::get<1>(container)), decltype(std::get<1>(container))>));
	}
}
