#include <string_view>
#include <charconv>

#include "gtest/gtest.h"

#include "lrl/iterators/tuple_iterator.hpp"

namespace
{
	decltype(auto) createSumLambda(float& sum)
	{
		return [&sum](auto&& value)
		{
			using T = std::decay_t<decltype(value)>;

			if constexpr(std::is_same_v<T, char>)
			{
				sum += value - '0';
				return;
			}

			if constexpr(std::is_same_v<T, std::string_view>)
			{
				sum += std::atoi(value.data());
				return;
			}

			if constexpr(std::is_arithmetic_v<T>)
			{
				sum += value;
				return;
			}
		};
	}
}

TEST(integration, tuple_iterator_AND_for_each)
{
	using namespace std::string_view_literals;

	const auto tuple = std::tuple{1, 2, "3"sv, '4', 5.f};
	float lrlSum = 0.f;
	lrl::algorithm::for_each
	(
		lrl::iterators::begin(tuple), 
		lrl::iterators::end(tuple), 
		createSumLambda(lrlSum)
	);

	float stlSum = 0.f;
	decltype(auto) stlSumLambda = createSumLambda(stlSum);
	std::invoke(stlSumLambda, std::get<0>(tuple));
	std::invoke(stlSumLambda, std::get<1>(tuple));
	std::invoke(stlSumLambda, std::get<2>(tuple));
	std::invoke(stlSumLambda, std::get<3>(tuple));
	std::invoke(stlSumLambda, std::get<4>(tuple));

	ASSERT_NE(stlSum, 0);
	ASSERT_NE(lrlSum, 0);
	ASSERT_EQ(stlSum, lrlSum);
}
