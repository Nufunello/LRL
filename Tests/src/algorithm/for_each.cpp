#include "gtest/gtest.h"

#include "lrl/algorithm/algorithm.hpp"

namespace
{
	template <template <typename> typename Container, bool Random = false, size_t... Indexes>
	Container<size_t> createVectorWithIndexes(std::index_sequence<Indexes...>)
	{
		Container<size_t> result {Indexes...};
		if constexpr(Random)
		{
			std::random_shuffle(std::begin(result), std::end(result));
		}
		return result;
	}

	decltype(auto) generateConcatanateLambda(std::string& stringReference)
	{
		return [&stringReference](const size_t index)
		{
			stringReference += std::to_string(index);
		};
	}
}

TEST(algorithm, for_each_stl_random)
{
	{
		std::string expected, actual = "";
		const auto vector = createVectorWithIndexes<std::vector>(std::make_index_sequence<1>{});
		
		EXPECT_FALSE(vector.empty());

		std::for_each
		(
			std::begin(vector), std::end(vector),
			generateConcatanateLambda(expected)
		);

		lrl::algorithm::for_each
		(
			std::begin(vector), std::end(vector),
			generateConcatanateLambda(actual)
		);

		ASSERT_EQ(expected, actual);
	}
	{
		std::string expected, actual = "";
		const auto vector = createVectorWithIndexes<std::vector, true>(std::make_index_sequence<255>{});
		
		EXPECT_FALSE(vector.empty());

		std::for_each
		(
			std::begin(vector), std::end(vector),
			generateConcatanateLambda(expected)
		);

		lrl::algorithm::for_each
		(
			std::begin(vector), std::end(vector),
			generateConcatanateLambda(actual)
		);

		ASSERT_EQ(expected, actual);
	}
}

TEST(algorithm, for_each_stl_ordered)
{
	{
		std::string expected, actual = "";
		const auto set = createVectorWithIndexes<std::set>(std::make_index_sequence<1>{});
		
		EXPECT_FALSE(set.empty());

		std::for_each
		(
			std::begin(set), std::end(set),
			generateConcatanateLambda(expected)
		);

		lrl::algorithm::for_each
		(
			std::begin(set), std::end(set),
			generateConcatanateLambda(actual)
		);

		ASSERT_EQ(expected, actual);
	}
	{
		std::string expected, actual = "";
		const auto set = createVectorWithIndexes<std::set>(std::make_index_sequence<255>{});
		
		EXPECT_FALSE(set.empty());

		std::for_each
		(
			std::begin(set), std::end(set),
			generateConcatanateLambda(expected)
		);

		lrl::algorithm::for_each
		(
			std::begin(set), std::end(set),
			generateConcatanateLambda(actual)
		);

		ASSERT_EQ(expected, actual);
	}
}

TEST(algorithm, for_each_stl_empty)
{
	std::string expected, actual = "";
	std::vector<size_t> vector;

	EXPECT_TRUE(vector.empty());
	
	std::for_each
	(
		std::begin(vector), std::end(vector),
		generateConcatanateLambda(expected)
	);

	lrl::algorithm::for_each
	(
		std::begin(vector), std::end(vector),
		generateConcatanateLambda(actual)
	);

	ASSERT_EQ(expected, actual);
}
