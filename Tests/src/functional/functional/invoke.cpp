#include "gtest/gtest.h"

#include "lrl/functional/functional.hpp"

namespace
{
	const int& max(const int& a, const int& b)
	{
		return (a > b ? (a) : (b));
	}

	struct dummy
	{
		int a;
		float b;
	};

	struct Const
	{
		float val;
		constexpr const float& method(int, float, double) const
		{
			return (val);
		}
	};

	struct NonConst
	{
		float val;
		float& method(int, float, double)
		{
			return (val);
		}
	};

	struct ConstAndNonConst
	{
		float val;
		constexpr const float& method(int, float, double) const
		{
			return (val);
		}
		float& method(int, float, double)
		{
			return (val);
		}
	};
}

TEST(functional, invoke_functor)
{
	const int a = 4;
	const int b = 5;
	EXPECT_EQ(&max(a, b), &lrl::functional::invoke(&max, a, b));
	auto max = [](const int& a, const int& b) -> const int& { return ::max(a,b); };
	EXPECT_EQ(&max(a, b), &lrl::functional::invoke(max, a, b));
}

TEST(functional, invoke_member)
{
	{
		dummy d{1,2.f};
		EXPECT_EQ(&d.a, &lrl::functional::invoke(&dummy::a, d));
		EXPECT_EQ(&d.b, &lrl::functional::invoke(&dummy::b, d));
	}
	{
		const dummy d{1,2.f};
		EXPECT_EQ(&d.a, &lrl::functional::invoke(&dummy::a, d));
		EXPECT_EQ(&d.b, &lrl::functional::invoke(&dummy::b, d));
	}
	{
		constexpr dummy d{1,2.f};
		constexpr auto actualA = lrl::functional::invoke(&dummy::a, d);
		EXPECT_EQ(d.a, actualA);
		constexpr auto actualB = lrl::functional::invoke(&dummy::b, d);
		EXPECT_EQ(d.b, actualB);
	}
}

TEST(functional, invoke_method)
{
	{
		const Const d{4};
		EXPECT_EQ(&d.method(1,2.f,3), &lrl::functional::invoke(&Const::method, d, 1,2.f,3));
	}
	{
		constexpr Const d{4};
		constexpr auto actual = lrl::functional::invoke(&Const::method, d, 1,2.f,3);
		EXPECT_EQ(d.method(1,2.f,3), actual);
	}
	{
		NonConst d{4};
		EXPECT_EQ(&d.method(1,2.f,3), &lrl::functional::invoke(&NonConst::method, d, 1,2.f,3));
	}
	{
		ConstAndNonConst d{4};
		EXPECT_EQ(&d.method(1,2.f,3), &lrl::functional::invoke(&ConstAndNonConst::method, d, 1,2.f,3));
	}
	{
		const ConstAndNonConst d{4};
		EXPECT_EQ(&d.method(1,2.f,3), &lrl::functional::invoke(&ConstAndNonConst::method, d, 1,2.f,3));
	}
	{
		constexpr ConstAndNonConst d{4};
		constexpr auto actual = lrl::functional::invoke(&ConstAndNonConst::method, d, 1,2.f,3);
		EXPECT_EQ(d.method(1,2.f,3), actual);
	}
}
