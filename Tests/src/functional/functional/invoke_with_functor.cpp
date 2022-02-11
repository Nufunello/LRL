#include <vector>
#include <functional>
#include <type_traits>

#include "gtest/gtest.h"

#include "lrl/functional/functional.hpp"

namespace
{
	template <typename T>
	struct dummy_functor
	{
		enum class ReturnType {};
		constexpr ReturnType operator()(T&& t){ return {}; }
	};

	template <>
	struct dummy_functor<double>
	{
		enum class ReturnType {};
		constexpr ReturnType operator()(const double& t){ return {}; }
	};

	template <template <typename> typename T, typename... Args>
	constexpr bool sameReturnType()
	{
		using Functor = T<Args...>;
		constexpr bool selfInvokeIsAsExpected = std::is_same_v
		<
			std::invoke_result_t<Functor, Args...>, 
			typename Functor::ReturnType
		>;
		constexpr bool invokeTemplateFunctorAsExpected = std::is_same_v
		<
			decltype(lrl::functional::invoke_template_functor<T>(Args{}...)),
			typename Functor::ReturnType
		>;
		return selfInvokeIsAsExpected && invokeTemplateFunctorAsExpected;
	}
}

TEST(functional, invoke_template_functor)
{
	{
		EXPECT_TRUE(std::invoke(::sameReturnType<::dummy_functor, int>))
			<< "call of functor \"dummy_functor\" should return dummy_functor::ReturnType";

		EXPECT_EQ
		(
			std::invoke(::dummy_functor<int>{}, int{}), 
			lrl::functional::invoke_template_functor<::dummy_functor>(int{})
		)
			<< "calls of functor \"dummy_functor\" should return same value";
	}
	{
		EXPECT_TRUE(std::invoke(::sameReturnType<::dummy_functor, double>))
			<< "call of functor \"dummy_functor\" should return dummy_functor::ReturnType";

		EXPECT_EQ
		(
			std::invoke(::dummy_functor<double>{}, double{}), 
			lrl::functional::invoke_template_functor<::dummy_functor>(double{})
		)
			<< "calls of functor \"dummy_functor\" should return same value";
	}
}
