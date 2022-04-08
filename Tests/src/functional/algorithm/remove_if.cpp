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

	template <auto... val>
	constexpr auto equal_to = [](const auto& current) { return ((current == val) || ...); };

	template <typename Container, typename Iterator>
	void erase(Container& c, Iterator&& i)
	{
		c.erase(i, std::end(c));
	}
}

TEST(algorithm, remove_if_stl_type)
{
	std::vector vector{1,2,3};
	using Expected = decltype(std::remove_if(std::begin(vector), std::end(vector), equal_to<1, 2, 3>));
	using Actual = decltype(lrl::algorithm::remove_if(std::begin(vector), std::end(vector), equal_to<1, 2, 3>));

	ASSERT_TRUE((std::is_same_v<Expected, Actual>));
}

TEST(algorithm, remove_if_stl_random)
{
	auto expected = createVectorWithIndexes<std::vector, true>(std::make_index_sequence<255>{});
	EXPECT_FALSE(expected.empty());
	auto actual = expected;

	decltype(auto) stlResult = std::remove_if(std::begin(expected), std::end(expected), equal_to<1, 2, 3>);
	decltype(auto) lrlResult = lrl::algorithm::remove_if(std::begin(actual), std::end(actual), equal_to<1, 2, 3>);
	ASSERT_EQ(std::distance(std::begin(expected), stlResult), std::distance(std::begin(actual), lrlResult));

	erase(expected, stlResult);
	erase(actual, lrlResult);

	ASSERT_EQ(expected, actual);
}

TEST(algorithm, remove_if_stl_different_predicate)
{
	std::vector<size_t> expected = {1, 2};
	EXPECT_FALSE(expected.empty());
	auto actual = expected;
	
	erase(expected, std::remove_if(std::begin(expected), std::end(expected), equal_to<1>));
	erase(actual, lrl::algorithm::remove_if(std::begin(actual), std::end(actual), equal_to<2>));

	ASSERT_NE(expected, actual);
}

TEST(algorithm, remove_if_stl_no_match)
{
	const std::vector<size_t> expected = {1, 2};
	EXPECT_FALSE(expected.empty());
	auto actual = expected;

	decltype(auto) lrlResult = lrl::algorithm::find_if(std::begin(actual), std::end(actual), equal_to<0>);
	erase(actual, lrlResult);
	ASSERT_EQ(expected, actual);
}

TEST(algorithm, remove_if_stl_empty)
{
	std::vector<size_t> expected;
	EXPECT_TRUE(expected.empty());
	auto actual = expected;
	
	erase(expected, std::remove_if(std::begin(expected), std::end(expected), equal_to<1>));
	erase(actual, lrl::algorithm::remove_if(std::begin(actual), std::end(actual), equal_to<2>));

	ASSERT_EQ(expected, actual);
}
