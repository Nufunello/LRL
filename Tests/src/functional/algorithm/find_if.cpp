#include "gtest/gtest.h"

#include <type_traits>

#include "lrl/algorithm/algorithm.hpp"

namespace
{
	template <template <typename...> typename Container, bool Random = false, size_t... Indexes>
	Container<size_t> createVectorWithIndexes(std::index_sequence<Indexes...>)
	{
		Container result{Indexes...};
		if constexpr(Random)
		{
			std::random_shuffle(std::begin(result), std::end(result));
		}
		return result;
	}

	template <auto val>
	constexpr auto equal_to = [](const auto& current) { return current == val; };
}

TEST(algorithm, find_if_stl_random)
{
	{
		const auto vector = createVectorWithIndexes<std::vector>(std::make_index_sequence<1>{});
		
		EXPECT_FALSE(vector.empty());

		decltype(auto) stlResult = std::find_if(std::begin(vector), std::end(vector), equal_to<1>);
		decltype(auto) lrlResult = lrl::algorithm::find_if(std::begin(vector), std::end(vector), equal_to<1>);

		ASSERT_TRUE((std::is_same_v<decltype(stlResult), decltype(lrlResult)>));
		ASSERT_EQ(stlResult, lrlResult);
	}
	{
		const auto vector = createVectorWithIndexes<std::vector, true>(std::make_index_sequence<255>{});
		
		EXPECT_FALSE(vector.empty());

		decltype(auto) stlResult = std::find_if(std::begin(vector), std::end(vector), equal_to<133>);
		decltype(auto) lrlResult = lrl::algorithm::find_if(std::begin(vector), std::end(vector), equal_to<133>);

		ASSERT_TRUE((std::is_same_v<decltype(stlResult), decltype(lrlResult)>));
		ASSERT_EQ(stlResult, lrlResult);
	}
}

TEST(algorithm, find_if_stl_not_equal)
{
	std::vector<size_t> vector = {1, 2};

	EXPECT_FALSE(vector.empty());
	
	decltype(auto) stlResult = std::find_if(std::begin(vector), std::end(vector), equal_to<1>);
	decltype(auto) lrlResult = lrl::algorithm::find_if(std::begin(vector), std::end(vector), equal_to<2>);

	ASSERT_TRUE((std::is_same_v<decltype(stlResult), decltype(lrlResult)>));
	ASSERT_NE(stlResult, lrlResult);
}

TEST(algorithm, find_if_stl_not_found)
{
	std::vector<size_t> vector = {1, 2};

	EXPECT_FALSE(vector.empty());
	
	decltype(auto) stlResult = std::find_if(std::begin(vector), std::end(vector), equal_to<0>);
	decltype(auto) lrlResult = lrl::algorithm::find_if(std::begin(vector), std::end(vector), equal_to<0>);

	ASSERT_TRUE((std::is_same_v<decltype(stlResult), decltype(lrlResult)>));
	ASSERT_EQ(stlResult, lrlResult);
}

TEST(algorithm, find_if_stl_empty)
{
	std::vector<size_t> vector;

	EXPECT_TRUE(vector.empty());
	
	decltype(auto) stlResult = std::find_if(std::begin(vector), std::end(vector), equal_to<1>);
	decltype(auto) lrlResult = lrl::algorithm::find_if(std::begin(vector), std::end(vector), equal_to<1>);

	ASSERT_TRUE((std::is_same_v<decltype(stlResult), decltype(lrlResult)>));
	ASSERT_EQ(stlResult, lrlResult);
}
