#pragma once

#include <type_traits>

#include "lrl/iterators/iterators.hpp"

#include "lrl/containers/get.hpp"

#include "lrl/algorithm/algorithm.hpp"

namespace lrl
{
	namespace iterators
	{
		template<std::size_t Index, typename Container>
		class index_iterator
		{
		public:
			constexpr index_iterator(Container container)
				: container{container}
			{}

#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator*()
			{
				return (lrl::containers::get<Index>(container));
			}

#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator*() const
			{
				return (lrl::containers::get<Index>(container));
			}
			
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr index_iterator<Index + 1, Container> operator++() const
			{
				return {container};
			}
			
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr index_iterator<Index + 1, Container> operator++(int) const
			{
				return {container};
			}
			
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr index_iterator<Index - 1, Container> operator--() const
			{
				return {container};
			}
			
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr index_iterator<Index - 1, Container> operator--(int) const
			{
				return {container};
			}

			template <size_t OtherIndex, typename OtherContainer>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr auto operator==(const index_iterator<OtherIndex, OtherContainer>&) const
				-> std::conditional_t<Index == OtherIndex, std::true_type, std::false_type>
			{
				static_assert(std::is_same_v<Container, OtherContainer>);
				return {};
			}

			template <size_t OtherIndex, typename OtherContainer>
#if __cplusplus >= 201703L
			[[nodiscard]]
#endif
			constexpr decltype(auto) operator!=(const index_iterator<OtherIndex, OtherContainer>& other) const
			{
				return !(index_iterator::operator==(other));
			}

		protected:
			Container container;
		};
	}

	namespace algorithm
	{
		template <size_t BeginIndex, size_t EndIndex, typename Container, typename Callable>
		struct for_each_algorithm<
			lrl::iterators::index_iterator<BeginIndex, Container>,
			lrl::iterators::index_iterator<EndIndex,   Container>,
			Callable>
		{
		private:
			template <size_t CurrentIndex, typename Functor>
			constexpr decltype(auto) invoke(
				const lrl::iterators::index_iterator<CurrentIndex, Container>& current,
				Functor&& functor)
			{
				std::invoke(functor, *current);
				return invoke(++current, std::forward<Functor>(functor));
			}
			template <typename Functor>
			constexpr decltype(auto) invoke(
				const lrl::iterators::index_iterator<EndIndex, Container>& current,
				Functor&& functor)
			{
				return std::forward<Functor>(functor);
			}

		public:
			template <typename Begin, typename End, typename Functor>
			constexpr decltype(auto) operator()(Begin&& begin, End&&, Functor&& functor)
			{
				return invoke(std::forward<Begin>(begin), std::forward<Functor>(functor));
			}
		};

		template <size_t BeginIndex, size_t EndIndex, typename Container, typename Predicate>
		struct find_if_algorithm<
			iterators::index_iterator<BeginIndex, Container>,
			iterators::index_iterator<EndIndex,   Container>,
			Predicate>
		{
		private:
			template <size_t CurrentIndex>
			constexpr decltype(auto) invoke(const iterators::index_iterator<CurrentIndex, Container>& current)
			{
				return dispatch(current, std::invoke_result_t<Predicate, decltype(*current)>{});
			}
			constexpr decltype(auto) invoke(const iterators::index_iterator<EndIndex, Container>& end)
			{
				return (end);
			}
			template <size_t CurrentIndex>
			constexpr decltype(auto) dispatch(const iterators::index_iterator<CurrentIndex, Container>& current, 
				std::true_type) 
			{
				return (current);
			}
			template <size_t CurrentIndex>
			constexpr decltype(auto) dispatch(const iterators::index_iterator<CurrentIndex, Container>& current, 
				std::false_type) 
			{
				return invoke(++current);
			}

		public:
			template <typename Begin, typename End, typename P>
			constexpr decltype(auto) operator()(Begin&& begin, End&& end, P&&)
			{
				return invoke(std::forward<Begin>(begin));
			}
		};
	}
}
