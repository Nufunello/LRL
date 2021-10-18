#include "gtest/gtest.h"

#include "lrl/iterators/tuple_iterator.hpp"

TEST(iterators, tuple_iterator_increment)
{
	using namespace std::literals;
	const auto tuple = std::tuple{1, ""sv, 2.f, "aaa"sv};
	
	const auto tuple0 = lrl::iterators::begin(tuple);
	const auto tuple1 = ++tuple0;
	const auto tuple2 = ++tuple1;
	const auto tuple3 = ++tuple2;

	{
		const auto& stl = std::get<0>(tuple);
		const auto& lrl = *tuple0;
		ASSERT_EQ(&stl, &lrl);
	}

	{
		const auto& stl = std::get<1>(tuple);
		const auto& lrl = *tuple1;
		ASSERT_EQ(&stl, &lrl);
	}

	{
		const auto& stl = std::get<2>(tuple);
		const auto& lrl = *tuple2;
		ASSERT_EQ(&stl, &lrl);
	}

	{
		const auto& stl = std::get<3>(tuple);
		const auto& lrl = *tuple3;
		ASSERT_EQ(&stl, &lrl);
	}
}

TEST(iterators, tuple_iterator_decrement)
{
	using namespace std::literals;
	const auto tuple = std::tuple{1, ""sv, 2.f, "aaa"sv};
	
	const auto tuple3 = --lrl::iterators::end(tuple);
	const auto tuple2 = --tuple3;
	const auto tuple1 = --tuple2;
	const auto tuple0 = --tuple1;

	{
		const auto& stl = std::get<3>(tuple);
		const auto& lrl = *tuple3;
		ASSERT_EQ(&stl, &lrl);
	}

	{
		const auto& stl = std::get<2>(tuple);
		const auto& lrl = *tuple2;
		ASSERT_EQ(&stl, &lrl);
	}

	{
		const auto& stl = std::get<1>(tuple);
		const auto& lrl = *tuple1;
		ASSERT_EQ(&stl, &lrl);
	}

	{
		const auto& stl = std::get<0>(tuple);
		const auto& lrl = *tuple0;
		ASSERT_EQ(&stl, &lrl);
	}
}

TEST(iterators, tuple_iterator_pre_post_increment_decrement_order)
{
	using namespace std::literals;
	const auto tuple = std::tuple{1, ""sv, 2.f, "aaa"sv};

	{
		const auto tuple0 = lrl::iterators::begin(tuple);
		ASSERT_EQ(++tuple0, tuple0++);

		const auto tuple1 = tuple0++;
		ASSERT_EQ(++tuple1, tuple1++);

		const auto tuple2 = tuple1++;
		ASSERT_EQ(++tuple2, tuple2++);

		const auto tuple3 = tuple2++;
		ASSERT_EQ(++tuple3, tuple3++);
	}

	{
		const auto tuple3 = lrl::iterators::end(tuple);
		ASSERT_EQ(--tuple3, tuple3--);

		const auto tuple2 = tuple3--;
		ASSERT_EQ(--tuple2, tuple2--);

		const auto tuple1 = tuple2--;
		ASSERT_EQ(--tuple1, tuple1--);

		const auto tuple0 = tuple1--;
		ASSERT_EQ(--tuple0, tuple0--);
	}
}
