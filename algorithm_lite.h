#include <iterator>  // std::distance, std::advance, std::next, std::iter_swap
#include <type_traits>  // std::is_base_of_v
#include <utility>      // std::pair, std::make_pair
                        // std::iterator_traits, std::random_access_iterator_tag

// Non-modifying sequence operations
//   Find
//   FindIf
//   FindIfNot
//   ForEach
//   ForEachN
//   Count
//   CountIf

// Modifying sequence operations
//   Copy
//   CopyIf
//   Generate
//   Reverse
//   Rotate

// Partitioning operations
//   IsPartitioned
//   Partition
//   PartitionCopy
//   std::stable_partition
//   std::partition_point
//   QuickSort

// Sorting operations
//   IsSort
//   IsSortedUntil
//   std::sort
//   std::stable_sort
//   std::partial_sort
//   std::nth_element

// Binary search operations (on sorted ranges)
//   LowerBound
//   UpperBound
//   BinarySearch
//   EqualRange

// Other operations on sorted ranges
//   Merge
//   std::inplace_merge
//   MergeSort

template <typename InputIt, typename T>
constexpr InputIt Find(InputIt first, InputIt last, const T& value) {
  for (; first != last; ++first) {
    if (*first == value) {
      return first;
    }
  }
  return last;
}

template <typename InputIt, typename UnaryPredicate>
constexpr InputIt FindIf(InputIt first, InputIt last, UnaryPredicate p) {
  for (; first != last; ++first) {
    if (p(*first)) {
      return first;
    }
  }
  return last;
}

template <typename InputIt, typename UnaryPredicate>
constexpr InputIt FindIfNot(InputIt first, InputIt last, UnaryPredicate q) {
  for (; first != last; ++first) {
    if (!q(*first)) {
      return first;
    }
  }
  return last;
}

template <typename InputIt, typename UnaryPredicate>
constexpr bool AllOf(InputIt first, InputIt last, UnaryPredicate p) {
  return FindIfNot(first, last, p) == last;
}

template <typename InputIt, typename UnaryPredicate>
constexpr bool AnyOf(InputIt first, InputIt last, UnaryPredicate p) {
  return FindIf(first, last, p) != last;
}

template <typename InputIt, typename UnaryPredicate>
constexpr bool NoneOf(InputIt first, InputIt last, UnaryPredicate p) {
  return FindIf(first, last, p) == last;
}

template <typename InputIt, typename UnaryFunction>
constexpr UnaryFunction ForEach(InputIt first, InputIt last, UnaryFunction f) {
  for (; first != last; ++first) {
    f(*first);
  }
  return f;
}

template <typename InputIt, typename Size, typename UnaryFunction>
InputIt ForEachN(InputIt first, Size n, UnaryFunction f) {
  for (Size i = 0; i < n; ++first, (void)++i) {
    f(*first);
  }
  return first;
}

template <typename InputIt, typename T>
typename std::iterator_traits<InputIt>::difference_type  //
Count(InputIt first, InputIt last, const T& value) {
  typename std::iterator_traits<InputIt>::difference_type ret = 0;
  for (; first != last; ++first) {
    if (*first == value) {
      ret++;
    }
  }
  return ret;
}

template <typename InputIt, typename UnaryPredicate>
typename std::iterator_traits<InputIt>::difference_type  //
CountIf(InputIt first, InputIt last, UnaryPredicate p) {
  typename std::iterator_traits<InputIt>::difference_type ret = 0;
  for (; first != last; ++first) {
    if (p(*first)) {
      ret++;
    }
  }
  return ret;
}

template <typename InputIt, typename OutputIt>
OutputIt Copy(InputIt first, InputIt last, OutputIt d_first) {
  for (; first != last; ++first, ++d_first) {
    *d_first = *first;
  }
  return d_first;
}

template <class InputIt, class OutputIt, class UnaryPredicate>
OutputIt CopyIf(InputIt first, InputIt last, OutputIt d_first,
                UnaryPredicate pred) {
  for (; first != last; ++first) {
    if (pred(*first)) {
      *d_first = *first;
      ++d_first;
    }
  }
  return d_first;
}

template <typename BidirIt>
void Reverse(BidirIt first, BidirIt last) {
  using iter_cat = typename std::iterator_traits<BidirIt>::iterator_category;

  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, iter_cat>) {
    if (first == last) return;
    for (--last; first < last; (void)++first, --last) {
      std::iter_swap(first, last);
    }
  } else {
    while ((first != last) && (first != --last)) {
      std::iter_swap(first++, last);
    }
  }
}

template <class ForwardIt>
ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last) {
  if (first == n_first) return last;
  if (n_first == last) return first;

  ForwardIt read = n_first;
  ForwardIt write = first;
  ForwardIt next_read = first;  // read position for when "read" hits "last"

  while (read != last) {
    if (write == next_read) next_read = read;  // track where "first" went
    std::iter_swap(write++, read++);
  }

  // rotate the remaining sequence into place
  (rotate)(write, next_read, last);
  return write;
}

template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
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

template <typename ForwardIt, typename T>
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

template <typename ForwardIt, typename T>
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

template <typename ForwardIt, typename T>
bool BinarySearch(ForwardIt first, ForwardIt last, const T& value) {
  first = LowerBound(first, last, value);
  return (!(first == last) && !(value < *first));
}

template <typename ForwardIt, typename T>
std::pair<ForwardIt, ForwardIt> EqualRange(ForwardIt first, ForwardIt last,
                                           const T& value) {
  return std::make_pair(LowerBound(first, last, value),
                        UpperBound(first, last, value));
}

template <typename ForwardIt, typename UnaryPredicate>
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
  auto pivot = *std::next(first, std::distance(first, last) / 2);
  ForwardIt middle1 = std::partition(
      first, last, [pivot](const auto& em) { return em < pivot; });
  ForwardIt middle2 = std::partition(
      middle1, last, [pivot](const auto& em) { return !(pivot < em); });
  quicksort(first, middle1);
  quicksort(middle2, last);
}
