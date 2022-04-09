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
			constexpr decltype(auto) operator()(Begin&& begin, End&&, P&&)
			{
				return invoke(std::forward<Begin>(begin));
			}
		};

		template <size_t BeginIndex, size_t EndIndex, typename Container, typename Predicate>
		struct remove_if_algorithm<
			iterators::index_iterator<BeginIndex, Container>,
			iterators::index_iterator<EndIndex,   Container>,
			Predicate>
		{
		private:
			template <std::size_t Index, typename Pred>
			struct IndexPredicate{};

			template <std::size_t... Indexes>
			struct IndexCollector
			{
				template <std::size_t Index, typename Pred>
				constexpr auto operator+(IndexPredicate<Index, Pred>) const
					-> std::conditional_t<std::is_same_v<Pred, std::false_type>, IndexCollector<Indexes..., Index>, IndexCollector<Indexes...>>
				{
					return {};
				}
			};

			template <size_t Index>
			using AdvancedIterator = iterators::index_iterator<BeginIndex + Index, Container>;

			template <size_t... Indexes>
			constexpr static decltype(auto) collectIndexes(std::index_sequence<Indexes...>) 
			{
				return (IndexCollector<>{} + ... + IndexPredicate<Indexes, 
					std::invoke_result_t<Predicate, decltype(*std::declval<AdvancedIterator<Indexes>>())>
				>{});
			}

			template <typename Iterator>
			struct Advancer
			{
				Iterator iterator;
				constexpr Advancer(Iterator iterator)
					: iterator{std::move(iterator)}
				{}
				template <typename T>
				constexpr decltype(auto) operator+(const T&) const
				{
					auto iterator = ++std::move(this->iterator);
					return Advancer<std::decay_t<decltype(iterator)>>{std::move(iterator)};
				}
			};
			template <typename Iterator, size_t... Indexes>
			constexpr static decltype(auto) advance(Iterator&& iterator, std::index_sequence<Indexes...>)
			{
				return (Advancer<std::decay_t<Iterator>>{std::forward<Iterator>(iterator)} + ... + Indexes).iterator;
			}

			template <template <typename...> typename T>
			struct TemplatedType
			{
				template <typename... Args>
				constexpr static decltype(auto) construct(Args&& ...args)
				{
					return T{std::forward<Args>(args)...};
				}
			};

			template <template <typename...> typename Base, typename... Elements>
			constexpr static auto getBase(const Base<Elements...>&) -> TemplatedType<Base>
			{
				return {};
			}

			template <size_t... Indexes>
			constexpr static decltype(auto) getByIndexes(iterators::index_iterator<BeginIndex, Container> begin,
				IndexCollector<Indexes...>) 
			{
				using Type = decltype(getBase(std::declval<Container>()));
				return Type::construct(*advance(begin, std::make_index_sequence<Indexes - BeginIndex>())...);
			}

		public:
			template <typename Begin, typename End, typename P>
			constexpr decltype(auto) operator()(Begin&& begin, End&&, P&&)
			{
				return getByIndexes(std::forward<Begin>(begin), collectIndexes(std::make_index_sequence<EndIndex - BeginIndex>()));
			}
		};
	}
}
