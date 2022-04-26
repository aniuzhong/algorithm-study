#include <utility>     // std::pair, std::make_pair
#include <type_traits> // std::is_base_of_v
#include <iterator>   // std::distance, std::advance, std::next, std::iter_swap
                      // std::iterator_traits, std::random_access_iterator_tag

// ForEach
// Copy
// Merge
// LowerBound
// UpperBound
// BinarySearch
// EqualRange
// FindIfNot
// Partition
// QuickSort
// Generate
// Reverse
// Unique
// IsSortedUntil

template<typename InputIt, typename UnaryFunction>
constexpr UnaryFunction ForEach(InputIt first, InputIt last, UnaryFunction f) {
  for (; first != last; ++first) {
    f(*first);
  }
}

template<typename InputIt, typename OutputIt>
OutputIt Copy(InputIt first, InputIt last,  OutputIt d_first) {
  for (; first != last; ++first, ++d_first) {
    *d_first = *first;
  }
  return d_first;
}

template<typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt Merge(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, InputIt2 last2,
               OutputIt d_first) {
  for (; first1 != last1; ++d_first) {
    if (first2 == last2) {
      return Copy(first1, last1, d_first);
    }
    if (*first2 < *first1) {
      *d_first = *first2;
      ++first2;
    } else {
      *d_first = *first1;
      ++first1;
    }
  }
  return Copy(first2, last2, d_first);
}

template<typename ForwardIt, typename T>
ForwardIt LowerBound(ForwardIt first, ForwardIt last, const T& value) {
  ForwardIt it;
  typename std::iterator_traits<ForwardIt>::difference_type count, step;
  count = std::distance(first, last);
  while (count > 0) {
    it = first;
    step = count / 2;
    std::advance(it, step);
    if (*it < value) {
      first = ++it;
      count -= step + 1;
    } else {
      count = step;
    }
  }
  return first;
}

template<typename ForwardIt, typename T>
ForwardIt UpperBound(ForwardIt first, ForwardIt last, const T& value) {
  ForwardIt it;
  typename std::iterator_traits<ForwardIt>::difference_type count, step;
  count = std::distance(first, last);
  while (count > 0) {
    it = first;
    step = count / 2;
    std::advance(it, step);
    if (!(*it > value)) {
      first = ++it;
      count -= step + 1;
    } else {
      count = step;
    }
  }
  return first;
}

template<typename ForwardIt, typename T>
bool BinarySearch(ForwardIt first, ForwardIt last, const T& value) {
  first = LowerBound(first, last, value);
  return (!(first == last) && !(value < *first));
}

template<typename ForwardIt, typename T>
std::pair<ForwardIt, ForwardIt> 
EqualRange(ForwardIt first, ForwardIt last, const T& value) {
  return std::make_pair(std::lower_bound(first, last, value),
                        std::upper_bound(first, last, value));
}

template<typename InputIt, typename UnaryPredicate>
constexpr InputIt FindIfNot(InputIt first, InputIt last, UnaryPredicate q) {
  for (; first != last; ++first) {
    if (!q(*first)) {
      return first;
    }
  }
  return last;
}

template<typename ForwardIt, typename UnaryPredicate>
ForwardIt Partition(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  first = FindIfNot(first, last, p);
  if (first == last) return first;

  for (ForwardIt i = std::next(first); i != last; ++i) {
    if (p(*i)) {
      std::iter_swap(i, first);
      ++first;
    }
  }
  return first;
}

template <typename ForwardIt>
void QuickSort(ForwardIt first, ForwardIt last) {
  if (first == last) return;
  auto pivot = *std::next(first, std::distance(first,last) / 2);
  ForwardIt middle1 = std::partition(first, last, 
                        [pivot](const auto& em) { return em < pivot; });
  ForwardIt middle2 = std::partition(middle1, last, 
                        [pivot](const auto& em) { return !(pivot < em); });
  quicksort(first, middle1);
  quicksort(middle2, last);
}

template<typename ForwardIt, typename Generator>
void Generate(ForwardIt first, ForwardIt last, Generator g) {
  while (first != last) {
    *first++ = g();
  }
}

template<typename BidirIt>
void Reverse(BidirIt first, BidirIt last)
{
  using iter_cat = typename std::iterator_traits<BidirIt>::iterator_category;

  // Tag dispatch, e.g. calling reverse_impl(first, last, iter_cat()),
  // can be used in C++14 and earlier modes.
  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, iter_cat>) {
    if (first == last)
      return;
    for (--last; first < last; (void)++first, --last) {
      std::iter_swap(first, last);
    }
  }
  else {
    while ((first != last) && (first != --last)) {
      std::iter_swap(first++, last);
    }
  }
}

template<typename ForwardIt>
ForwardIt Unique(ForwardIt first, ForwardIt last) {
  if (first == last)
      return last;

  ForwardIt result = first;
  while (++first != last) {
    if (!(*result == *first) && ++result != first) {
      *result = std::move(*first);
    }
  }
  return ++result;
}

template <typename ForwardIt, typename Compare>
ForwardIt IsSortedUntil(ForwardIt first, ForwardIt last, Compare comp)  {
  if (first != last) {
    ForwardIt next = first;
    while (++next != last) {
      if (comp(*next, *first))
        return next;
      first = next;
    }
  }
  return last;
}