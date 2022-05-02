#ifndef MEMORY_LITE_IMPL_H
#define MEMORY_LITE_IMPL_H

#include <type_traits>  // std::enable_if, std::is_object
#include <utility>      // std::pair

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
    Destroy(d_first, current);
    throw;
  }
}

template <typename InputIt, typename Size, typename NoThrowForwardIt>
std::pair<InputIt, NoThrowForwardIt>  //
UninitializedMoveN(InputIt first, Size count, NoThrowForwardIt d_first) {
  using Value = typename std::iterator_traits<NoThrowForwardIt>::value_type;
  NoThrowForwardIt current = d_first;
  try {
    for (; count > 0; ++first, (void)++current, --count) {
      ::new (const_cast<void*>(static_cast<const volatile void*>(
          AddressOf(*current)))) Value(std::move(*first));
    }
  } catch (...) {
    Destroy(d_first, current);
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
    Destroy(first, current);
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
          static_cast<const volatile void*>(AddressOf(*current)))) T;
    }
    return current;
  } catch (...) {
    Destroy(first, current);
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
          static_cast<const volatile void*>(AddressOf(*current)))) Value();
    }
  } catch (...) {
    Destroy(first, current);
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
          static_cast<const volatile void*>(AddressOf(*current)))) T();
    }
    return current;
  } catch (...) {
    Destroy(first, current);
    throw;
  }
}

template <typename ForwardIt>
void Destroy(ForwardIt first, ForwardIt last) {
  for (; first != last; ++first) DestroyAt(AddressOf(*first));
}

template <typename ForwardIt, typename Size>
ForwardIt DestroyN(ForwardIt first, Size n) {
  for (; n > 0; (void)++first, --n) Destroy_at(AddressOf(*first));
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

#endif  // MEMORY_LITE_IMPL_H