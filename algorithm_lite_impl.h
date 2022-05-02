#ifndef ALGORITHM_LITE_IMPL_H
#define ALGORITHM_LITE_IMPL_H

#include <iterator>  // std::distance, std::advance, std::next, std::iter_swap
#include <memory>
#include <new>
#include <type_traits>  // std::is_base_of_v
#include <utility>      // std::make_pair, std::move
                        // std::random_access_iterator_tag

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

template <typename InputIt, typename OutputIt, typename UnaryPredicate>
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

template <typename ForwardIt, typename T>
void Fill(ForwardIt first, ForwardIt last, const T& value) {
  for (; first != last; ++first) {
    *first = value;
  }
}

template <typename OutputIt, typename Size, typename T>
OutputIt FillN(OutputIt first, Size count, const T& value) {
  for (Size i = 0; i < count; i++) {
    *first++ = value;
  }
  return first;
}

template <typename ForwardIt, typename T>
ForwardIt Remove(ForwardIt first, ForwardIt last, const T& value) {
  first = Find(first, last, value);
  if (first != last)
    for (ForwardIt i = first; ++i != last;)
      if (!(*i == value)) *first++ = std::move(*i);
  return first;
}

template <typename ForwardIt, typename UnaryPredicate>
ForwardIt RemoveIf(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  first = FindIf(first, last, p);
  if (first != last)
    for (ForwardIt i = first; ++i != last;)
      if (!p(*i)) *first++ = std::move(*i);
  return first;
}

template <typename ForwardIt, typename T>
void Replace(ForwardIt first, ForwardIt last, const T& old_value,
             const T& new_value) {
  for (; first != last; ++first) {
    if (*first == old_value) {
      *first = new_value;
    }
  }
}

template <typename ForwardIt, typename UnaryPredicate, typename T>
void ReplaceIf(ForwardIt first, ForwardIt last, UnaryPredicate p,
               const T& new_value) {
  for (; first != last; ++first) {
    if (p(*first)) {
      *first = new_value;
    }
  }
}
template <typename ForwardIt1, typename ForwardIt2>
void IterSwap(ForwardIt1 a, ForwardIt2 b) {
  using std::swap;
  swap(*a, *b);
}

template <typename ForwardIt>
void SelectionSort(ForwardIt first, ForwardIt last) {
  for (ForwardIt i = first; i != last; ++i) IterSwap(i, MinElement(i, last));
}

template <typename BidirIt>
void Reverse(BidirIt first, BidirIt last) {
  using iter_cat = typename std::iterator_traits<BidirIt>::iterator_category;

  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, iter_cat>) {
    if (first == last) return;
    for (--last; first < last; (void)++first, --last) {  // support operator<()
      IterSwap(first, last);
    }
  } else {
    while ((first != last) && (first != --last)) {
      IterSwap(first++, last);
    }
  }
}

template <typename ForwardIt>
ForwardIt Rotate(ForwardIt first, ForwardIt n_first, ForwardIt last) {
  if (first == n_first) return last;
  if (n_first == last) return first;

  ForwardIt read = n_first;
  ForwardIt write = first;
  ForwardIt next_read = first;  // read position for when "read" hits "last"

  while (read != last) {
    if (write == next_read) next_read = read;  // track where "first" went
    IterSwap(write++, read++);
  }

  // rotate the remaining sequence into place
  (Rotate)(write, next_read, last);
  return write;
}

template <typename ForwardIt>
void InsertionSort(ForwardIt first, ForwardIt last) {
  for (auto it = first; it != last; ++it) {
    Rotate(UpperBound(first, it, *it), it, std::next(it, 1));
  }
}

template <typename ForwardIt>
ForwardIt Unique(ForwardIt first, ForwardIt last) {
  if (first == last) return last;

  ForwardIt result = first;
  while (++first != last) {
    if (!(*result == *first) && ++result != first) {
      *result = std::move(*first);
    }
  }
  return ++result;
}

template <typename InputIt, typename UnaryPredicate>
bool IsPartitioned(InputIt first, InputIt last, UnaryPredicate p) {
  for (; first != last; ++first)
    if (!p(*first)) break;
  for (; first != last; ++first)
    if (p(*first)) return false;
  return true;
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
  ForwardIt middle1 = Partition(
      first, last, [pivot](const auto& em) { return em < pivot; });  //
  ForwardIt middle2 = Partition(
      middle1, last, [pivot](const auto& em) { return !(pivot < em); });
  QuickSort(first, middle1);
  QuickSort(middle2, last);
}

template <typename ForwardIt>
ForwardIt IsSortedUntil(ForwardIt first, ForwardIt last) {
  return IsSortedUntil(first, last, std::less<>());
}

template <typename ForwardIt, typename Compare>
ForwardIt IsSortedUntil(ForwardIt first, ForwardIt last, Compare comp) {
  if (first != last) {
    ForwardIt next = first;
    while (++next != last) {
      if (comp(*next, *first)) return next;
      first = next;
    }
  }
  return last;
}

template <class ForwardIt>
bool IsSort(ForwardIt first, ForwardIt last) {
  return IsSortedUntil(first, last) == last;
}

template <class ForwardIt, class Compare>
bool IsSort(ForwardIt first, ForwardIt last, Compare comp) {
  return IsSortedUntil(first, last, comp) == last;
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

template <typename InputIt1, typename InputIt2>
bool Includes(InputIt1 first1, InputIt1 last1, InputIt2 first2,
              InputIt2 last2) {
  for (; first2 != last2; ++first1) {
    if (first1 == last1 || *first2 < *first1) return false;
    if (!(*first1 < *first2)) ++first2;
  }
  return true;
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

template <typename Iter>
void MergeSort(Iter first, Iter last) {
  if (last - first > 1) {
    Iter middle = first + (last - first) / 2;
    MergeSort(first, middle);
    MergeSort(middle, last);
    std::inplace_merge(first, middle, last);
  }
}

template <typename ForwardIt>
ForwardIt MinElement(ForwardIt first, ForwardIt last) {
  if (first == last) return last;

  ForwardIt smallest = first;
  ++first;
  for (; first != last; ++first) {
    if (*first < *smallest) {
      smallest = first;
    }
  }
  return smallest;
}

template <typename T>
typename std::enable_if<std::is_object<T>::value, T*>::type  //
AddressOf(T& arg) noexcept {
  return reinterpret_cast<T*>(
      &const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
}

template <typename T>
typename std::enable_if<!std::is_object<T>::value, T*>::type  //
AddressOf(T& arg) noexcept {
  return &arg;
}

template <typename InputIt, typename NoThrowForwardIt>
NoThrowForwardIt UninitializedCopy(InputIt first, InputIt last,
                                   NoThrowForwardIt d_first) {
  using T = typename std::iterator_traits<NoThrowForwardIt>::value_type;
  NoThrowForwardIt current = d_first;
  try {
    for (; first != last; ++first, (void)++current) {
      ::new (const_cast<void*>(
          static_cast<const volatile void*>(AddressOf(*current)))) T(*first);
    }
    return current;
  } catch (...) {
    for (; d_first != current; ++d_first) {
      d_first->~T();
    }
    throw;
  }
}

template <typename InputIt, typename Size, typename NoThrowForwardIt>
NoThrowForwardIt UninitializedCopyN(InputIt first, Size count,
                                    NoThrowForwardIt d_first) {
  using T = typename std::iterator_traits<NoThrowForwardIt>::value_type;
  NoThrowForwardIt current = d_first;
  try {
    for (; count > 0; ++first, (void)++current, --count) {
      ::new (const_cast<void*>(
          static_cast<const volatile void*>(AddressOf(*current)))) T(*first);
    }
  } catch (...) {
    for (; d_first != current; ++d_first) {
      d_first->~T();
    }
    throw;
  }
  return current;
}

template <typename ForwardIt, typename T>
void UninitializedFill(ForwardIt first, ForwardIt last, const T& value) {
  using V = typename std::iterator_traits<ForwardIt>::value_type;
  ForwardIt current = first;
  try {
    for (; current != last; ++current) {
      ::new (const_cast<void*>(
          static_cast<const volatile void*>(AddressOf(*current)))) V(value);
    }
  } catch (...) {
    for (; first != current; ++first) {
      first->~V();
    }
    throw;
  }
}

template <typename ForwardIt, typename Size, typename T>
ForwardIt UninitializedFillN(ForwardIt first, Size count, const T& value) {
  using V = typename std::iterator_traits<ForwardIt>::value_type;
  ForwardIt current = first;
  try {
    for (; count > 0; ++current, (void)--count) {
      ::new (const_cast<void*>(
          static_cast<const volatile void*>(AddressOf(*current)))) V(value);
    }
    return current;
  } catch (...) {
    for (; first != current; ++first) {
      first->~V();
    }
    throw;
  }
}

template <typename InputIt, typename NoThrowForwardIt>
NoThrowForwardIt UninitializedMove(InputIt first, InputIt last,
                                   NoThrowForwardIt d_first) {
  using Value = typename std::iterator_traits<NoThrowForwardIt>::value_type;
  NoThrowForwardIt current = d_first;
  try {
    for (; first != last; ++first, (void)++current) {
      ::new (const_cast<void*>(static_cast<const volatile void*>(
          AddressOf(*current)))) Value(std::move(*first));
    }
    return current;
  } catch (...) {
    std::destroy(d_first, current);
    throw;
  }
}

template <typename InputIt, typename Size, typename NoThrowForwardIt>
std::pair<InputIt, NoThrowForwardIt> UninitializedMoveN(
    InputIt first, Size count, NoThrowForwardIt d_first) {
  using Value = typename std::iterator_traits<NoThrowForwardIt>::value_type;
  NoThrowForwardIt current = d_first;
  try {
    for (; count > 0; ++first, (void)++current, --count) {
      ::new (const_cast<void*>(static_cast<const volatile void*>(
          AddressOf(*current)))) Value(std::move(*first));
    }
  } catch (...) {
    std::destroy(d_first, current);
    throw;
  }
  return {first, current};
}

template <typename ForwardIt>
void UninitializedDefaultConstruct(ForwardIt first, ForwardIt last) {
  using Value = typename std::iterator_traits<ForwardIt>::value_type;
  ForwardIt current = first;
  try {
    for (; current != last; ++current) {
      ::new (const_cast<void*>(
          static_cast<const volatile void*>(AddressOf(*current)))) Value;
    }
  } catch (...) {
    std::destroy(first, current);
    throw;
  }
}

template <typename ForwardIt, typename Size>
ForwardIt UninitializedDefaultConstructN(ForwardIt first, Size n) {
  using T = typename std::iterator_traits<ForwardIt>::value_type;
  ForwardIt current = first;
  try {
    for (; n > 0; (void)++current, --n) {
      ::new (const_cast<void*>(
          static_cast<const volatile void*>(std::addressof(*current)))) T;
    }
    return current;
  } catch (...) {
    std::destroy(first, current);
    throw;
  }
}

template <typename ForwardIt>
void UninitializedValueConstruct(ForwardIt first, ForwardIt last) {
  using Value = typename std::iterator_traits<ForwardIt>::value_type;
  ForwardIt current = first;
  try {
    for (; current != last; ++current) {
      ::new (const_cast<void*>(
          static_cast<const volatile void*>(std::addressof(*current)))) Value();
    }
  } catch (...) {
    std::destroy(first, current);
    throw;
  }
}

template <typename ForwardIt, typename Size>
ForwardIt UninitializedValueConstructN(ForwardIt first, Size n) {
  using T = typename std::iterator_traits<ForwardIt>::value_type;
  ForwardIt current = first;
  try {
    for (; n > 0; (void)++current, --n) {
      ::new (const_cast<void*>(
          static_cast<const volatile void*>(std::addressof(*current)))) T();
    }
    return current;
  } catch (...) {
    std::destroy(first, current);
    throw;
  }
}

template <typename ForwardIt>
void Destroy(ForwardIt first, ForwardIt last) {
  for (; first != last; ++first) DestroyAt(std::addressof(*first));
}

template <typename ForwardIt, typename Size>
ForwardIt DestroyN(ForwardIt first, Size n) {
  for (; n > 0; (void)++first, --n) std::destroy_at(std::addressof(*first));
  return first;
}

template <typename T, typename... Args>
constexpr T* ConstructAt(T* p, Args&&... args) {
  return ::new (const_cast<void*>(static_cast<const volatile void*>(p)))
      T(std::forward<Args>(args)...);
}

template <typename T>
constexpr void DestroyAt(T* p) {
  if constexpr (std::is_array_v<T>) {
    for (auto& elem : *p) {
      (DestroyAt)(AddressOf(elem));
    }
  } else {
    p->~T();
  }
}

#endif  // ALGORITHM_LITE_IMPL_H
