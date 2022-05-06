#ifndef ALGORITHM_LITE_H
#define ALGORITHM_LITE_H

#include <algorithm>  // std::inplace_merge
#include <iterator>   // std::iterator_traits
#include <utility>    // std::pair, std::swap

// Non-modifying sequence operations
//   AllOf
template <typename InputIt, typename UnaryPredicate>
constexpr bool AllOf(InputIt first, InputIt last, UnaryPredicate p);
//   AnyOf
template <typename InputIt, typename UnaryPredicate>
constexpr bool AnyOf(InputIt first, InputIt last, UnaryPredicate p);
//   NoneOf
template <typename InputIt, typename UnaryPredicate>
constexpr bool NoneOf(InputIt first, InputIt last, UnaryPredicate p);
//   ForEach
template <typename InputIt, typename UnaryFunction>
constexpr UnaryFunction ForEach(InputIt first, InputIt last, UnaryFunction f);
//   ForEachN
template <typename InputIt, typename Size, typename UnaryFunction>
InputIt ForEachN(InputIt first, Size n, UnaryFunction f);
//   Count
template <typename InputIt, typename T>
typename std::iterator_traits<InputIt>::difference_type  //
Count(InputIt first, InputIt last, const T& value);
//   CountIf
template <typename InputIt, typename UnaryPredicate>
typename std::iterator_traits<InputIt>::difference_type  //
CountIf(InputIt first, InputIt last, UnaryPredicate p);
//   Mismatch
template <class InputIt1, class InputIt2>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2) {
  while (first1 != last1 && *first1 == *first2) {
    ++first1, ++first2;
  }
  return std::make_pair(first1, first2);
}
template <class InputIt1, class InputIt2, class BinaryPredicate>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2, BinaryPredicate p) {
  while (first1 != last1 && p(*first1, *first2)) {
    ++first1, ++first2;
  }
  return std::make_pair(first1, first2);
}
template <class InputIt1, class InputIt2>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2, InputIt2 last2) {
  while (first1 != last1 && first2 != last2 && *first1 == *first2) {
    ++first1, ++first2;
  }
  return std::make_pair(first1, first2);
}
template <class InputIt1, class InputIt2, class BinaryPredicate>
std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1,
                                       InputIt2 first2, InputIt2 last2,
                                       BinaryPredicate p) {
  while (first1 != last1 && first2 != last2 && p(*first1, *first2)) {
    ++first1, ++first2;
  }
  return std::make_pair(first1, first2);
}
//   Find
template <typename InputIt, typename T>
constexpr InputIt Find(InputIt first, InputIt last, const T& value);
//   FindIf
template <typename InputIt, typename UnaryPredicate>
constexpr InputIt FindIf(InputIt first, InputIt last, UnaryPredicate p);
//   FindIfNot
template <typename InputIt, typename UnaryPredicate>
constexpr InputIt FindIfNot(InputIt first, InputIt last, UnaryPredicate q);
//   FindEnd
template <class ForwardIt1, class ForwardIt2>
ForwardIt1 FindEnd(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first,
                   ForwardIt2 s_last) {
  if (s_first == s_last) return last;
  ForwardIt1 result = last;
  while (true) {
    ForwardIt1 new_result = std::search(first, last, s_first, s_last);
    if (new_result == last) {
      break;
    } else {
      result = new_result;
      first = result;
      ++first;
    }
  }
  return result;
}
template <class ForwardIt1, class ForwardIt2, class BinaryPredicate>
ForwardIt1 FindEnd(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first,
                   ForwardIt2 s_last, BinaryPredicate p) {
  if (s_first == s_last) return last;
  ForwardIt1 result = last;
  while (true) {
    ForwardIt1 new_result = std::search(first, last, s_first, s_last, p);
    if (new_result == last) {
      break;
    } else {
      result = new_result;
      first = result;
      ++first;
    }
  }
  return result;
}
//   FindFirstOf
template <class InputIt, class ForwardIt>
InputIt FindFirstOf(InputIt first, InputIt last, ForwardIt s_first,
                    ForwardIt s_last) {
  for (; first != last; ++first) {
    for (ForwardIt it = s_first; it != s_last; ++it) {
      if (*first == *it) {
        return first;
      }
    }
  }
  return last;
}
//   AjacentFind
template <class ForwardIt>
ForwardIt AjacentFind(ForwardIt first, ForwardIt last) {
  if (first == last) {
    return last;
  }
  ForwardIt next = first;
  ++next;
  for (; next != last; ++next, ++first) {
    if (*first == *next) {
      return first;
    }
  }
  return last;
}
template <class ForwardIt, class BinaryPredicate>
ForwardIt AjacentFind(ForwardIt first, ForwardIt last, BinaryPredicate p) {
  if (first == last) {
    return last;
  }
  ForwardIt next = first;
  ++next;
  for (; next != last; ++next, ++first) {
    if (p(*first, *next)) {
      return first;
    }
  }
  return last;
}
//   Search
template <class ForwardIt1, class ForwardIt2>
constexpr ForwardIt1 Search(ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 s_first, ForwardIt2 s_last) {
  while (1) {
    ForwardIt1 it = first;
    for (ForwardIt2 s_it = s_first;; ++it, ++s_it) {
      if (s_it == s_last) return first;
      if (it == last) return last;
      if (!(*it == *s_it)) break;
    }
    ++first;
  }
}
template <class ForwardIt1, class ForwardIt2, class BinaryPredicate>
constexpr ForwardIt1 Search(ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 s_first, ForwardIt2 s_last,
                            BinaryPredicate p) {
  while (1) {
    ForwardIt1 it = first;
    for (ForwardIt2 s_it = s_first;; ++it, ++s_it) {
      if (s_it == s_last) return first;
      if (it == last) return last;
      if (!p(*it, *s_it)) break;
    }
    ++first;
  }
}
//   SearchN
template <class ForwardIt, class Size, class T>
ForwardIt SearchN(ForwardIt first, ForwardIt last, Size count, const T& value) {
  if (count <= 0) {
    return first;
  }
  for (; first != last; ++first) {
    if (!(*first == value)) {
      continue;
    }

    ForwardIt candidate = first;
    Size cur_count = 0;

    while (true) {
      ++cur_count;
      if (cur_count >= count) {
        // success
        return candidate;
      }
      ++first;
      if (first == last) {
        // exhausted the list
        return last;
      }
      if (!(*first == value)) {
        // too few in a row
        break;
      }
    }
  }
  return last;
}
template <class ForwardIt, class Size, class T, class BinaryPredicate>
ForwardIt SearchN(ForwardIt first, ForwardIt last, Size count, const T& value,
                  BinaryPredicate p) {
  if (count <= 0) {
    return first;
  }
  for (; first != last; ++first) {
    if (!p(*first, value)) {
      continue;
    }

    ForwardIt candidate = first;
    Size cur_count = 0;

    while (true) {
      ++cur_count;
      if (cur_count >= count) {
        // success
        return candidate;
      }
      ++first;
      if (first == last) {
        // exhausted the list
        return last;
      }
      if (!p(*first, value)) {
        // too few in a row
        break;
      }
    }
  }
  return last;
}

// Modifying sequence operations
//   Copy
template <typename InputIt, typename OutputIt>
OutputIt Copy(InputIt first, InputIt last, OutputIt d_first);
//   CopyIf
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
OutputIt CopyIf(InputIt first, InputIt last, OutputIt d_first,
                UnaryPredicate pred);
//   Fill
template <typename ForwardIt, typename T>
void Fill(ForwardIt first, ForwardIt last, const T& value);
//   FillN
template <typename OutputIt, typename Size, typename T>
OutputIt FillN(OutputIt first, Size count, const T& value);
//   Remove
template <typename ForwardIt, typename T>
ForwardIt Remove(ForwardIt first, ForwardIt last, const T& value);
//   RemoveIf
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt RemoveIf(ForwardIt first, ForwardIt last, UnaryPredicate p);
//   Replace
template <typename ForwardIt, typename T>
void Replace(ForwardIt first, ForwardIt last, const T& old_value,
             const T& new_value);
//   ReplaceIf
template <typename ForwardIt, typename UnaryPredicate, typename T>
void ReplaceIf(ForwardIt first, ForwardIt last, UnaryPredicate p,
               const T& new_value);
//   IterSwap
template <typename ForwardIt1, typename ForwardIt2>
void IterSwap(ForwardIt1 a, ForwardIt2 b);
//   SelectionSort
template <typename ForwardIt>
void SelectionSort(ForwardIt first, ForwardIt last);
//   Reverse
template <typename BidirIt>
void Reverse(BidirIt first, BidirIt last);
//   Rotate
template <typename ForwardIt>
ForwardIt Rotate(ForwardIt first, ForwardIt n_first, ForwardIt last);
//   InsertionSort
template <typename ForwardIt>
void InsertionSort(ForwardIt first, ForwardIt last);
//   Unique
template <typename ForwardIt>
ForwardIt Unique(ForwardIt first, ForwardIt last);

// Partitioning operations
// IsPartitioned
template <typename InputIt, typename UnaryPredicate>
bool IsPartitioned(InputIt first, InputIt last, UnaryPredicate p);
//   Partition
template <typename ForwardIt, typename UnaryPredicate>
ForwardIt Partition(ForwardIt first, ForwardIt last, UnaryPredicate p);
//   std::stable_partition
//   std::partition_point
//   QuickSort
template <typename ForwardIt>
void QuickSort(ForwardIt first, ForwardIt last);

// Sorting operations
//   IsSortedUntil
template <typename ForwardIt>
ForwardIt IsSortedUntil(ForwardIt first, ForwardIt last);
template <typename ForwardIt, typename Compare>
ForwardIt IsSortedUntil(ForwardIt first, ForwardIt last, Compare comp);
//   IsSort
template <class ForwardIt>
bool IsSort(ForwardIt first, ForwardIt last);
template <class ForwardIt, class Compare>
bool IsSort(ForwardIt first, ForwardIt last, Compare comp);
//   std::sort
//   std::stable_sort
//   std::partial_sort
//   std::nth_element

// Binary search operations (on sorted ranges)
//   LowerBound
template <typename ForwardIt, typename T>
ForwardIt UpperBound(ForwardIt first, ForwardIt last, const T& value);
//   UpperBound
template <typename ForwardIt, typename T>
ForwardIt UpperBound(ForwardIt first, ForwardIt last, const T& value);
//   BinarySearch
template <typename ForwardIt, typename T>
bool BinarySearch(ForwardIt first, ForwardIt last, const T& value);
//   EqualRange
template <typename ForwardIt, typename T>
std::pair<ForwardIt, ForwardIt> EqualRange(ForwardIt first, ForwardIt last,
                                           const T& value);

// Set operations (on sorted ranges)
//   Includes
template <typename InputIt1, typename InputIt2>
bool Includes(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2);

// Other operations on sorted ranges
//   Merge
template <typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
               OutputIt d_first);
//   std::inplace_merge
//   MergeSort
template <typename Iter>
void MergeSort(Iter first, Iter last);

// Minimum/maximum operations
//   MinElement
template <typename ForwardIt>
ForwardIt MinElement(ForwardIt first, ForwardIt last);

// Include implementation.
#include "algorithm_lite_impl.h"

#endif  // ALGORITHM_LITE_H
