#include <string_view>
#include <charconv>

#include "gtest/gtest.h"

#include "lrl/iterators/tuple_iterator.hpp"
#include "lrl/iterators/type_array_iterator.hpp"

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

	template <typename T>
	decltype(auto) createCountTypeLambda(std::size_t& cTypes)
	{
		return [&cTypes](const auto type) mutable 
		{ 
			cTypes += type == lrl::containers::type<T>{} ? 1 : 0; 
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

TEST(integration, type_array_iterator_AND_for_each)
{
	const auto typeArray = lrl::containers::type_array<std::string_view, std::string, float, int, float>{};
	{
		std::size_t cFloats = 0;
		lrl::algorithm::for_each
		(
			lrl::iterators::begin(typeArray), 
			lrl::iterators::end(typeArray), 
			createCountTypeLambda<float>(cFloats)
		);
		ASSERT_EQ(cFloats, 2);
	}
	{
		std::size_t cInt = 0;
		lrl::algorithm::for_each
		(
			lrl::iterators::begin(typeArray), 
			lrl::iterators::end(typeArray), 
			createCountTypeLambda<int>(cInt)
		);
		ASSERT_EQ(cInt, 1);
	}
	{
		std::size_t cChar = 0;
		lrl::algorithm::for_each
		(
			lrl::iterators::begin(typeArray), 
			lrl::iterators::end(typeArray), 
			createCountTypeLambda<char>(cChar)
		);
		ASSERT_EQ(cChar, 0);
	}
}

TEST(integration, tuple_iterator_AND_find_if)
{
	using namespace std::string_view_literals;

	const auto tuple = std::tuple{1, 2, "3"sv, '4', 5.f};
	constexpr auto findInt = [](const auto& val)
		{
			using Argument = std::decay_t<decltype(val)>;
			return std::conditional_t<std::is_same_v<Argument, int>, std::true_type, std::false_type>{};
		};

	const auto floa = lrl::algorithm::find_if
	(
		lrl::iterators::begin(tuple),
		lrl::iterators::end(tuple),
		[](const auto& val)
		{
			using Argument = std::decay_t<decltype(val)>;
			return std::conditional_t<std::is_same_v<Argument, float>, std::true_type, std::false_type>{};
		}
	);
	ASSERT_EQ(*floa, std::get<4>(tuple));

	const auto firstInt = lrl::algorithm::find_if
	(
		lrl::iterators::begin(tuple),
		lrl::iterators::end(tuple),
		findInt
	);
	ASSERT_EQ(*firstInt, std::get<0>(tuple));
	const auto secondInt = lrl::algorithm::find_if
	(
		++firstInt,
		lrl::iterators::end(tuple),
		findInt
	);
	ASSERT_EQ(*secondInt, std::get<1>(tuple));

	const auto end = lrl::algorithm::find_if
	(
		lrl::iterators::begin(tuple),
		lrl::iterators::end(tuple),
		[](const auto& val)
		{
			using Argument = std::decay_t<decltype(val)>;
			return std::conditional_t<std::is_same_v<Argument, double>, std::true_type, std::false_type>{};
		}
	);
	ASSERT_EQ(end, lrl::iterators::end(tuple));
}

TEST(integration, type_array_iterator_AND_find_if)
{
	const auto typeArray = lrl::containers::type_array<std::string_view, std::string, float, int, std::string>{};
	const auto firstString = lrl::algorithm::find_if
		(
			lrl::iterators::begin(typeArray), 
			lrl::iterators::end(typeArray), 
			[](const auto val)
			{
				using Argument = std::decay_t<decltype(val)>;
				return std::conditional_t<std::is_same_v<Argument, lrl::containers::type<std::string>>, std::true_type, std::false_type>{};
			}
		);
	ASSERT_EQ(*firstString, lrl::containers::type<std::string>{});
	const auto secondString = lrl::algorithm::find_if
		(
			++firstString, 
			lrl::iterators::end(typeArray), 
			[](const auto val)
			{
				using Argument = std::decay_t<decltype(val)>;
				return std::conditional_t<std::is_same_v<Argument, lrl::containers::type<std::string>>, std::true_type, std::false_type>{};
			}
		);
	ASSERT_EQ(*secondString, lrl::containers::type<std::string>{});

	const auto integer = lrl::algorithm::find_if
		(
			lrl::iterators::begin(typeArray), 
			lrl::iterators::end(typeArray), 
			[](const auto val)
			{
				using Argument = std::decay_t<decltype(val)>;
				return std::conditional_t<std::is_same_v<Argument, lrl::containers::type<int>>, std::true_type, std::false_type>{};
			}
		);
	ASSERT_EQ(*integer, lrl::containers::type<int>{});
}
