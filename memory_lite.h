#ifndef MEMORY_LITE_H
#define MEMORY_LITE_H

#include <utility>  // std::pair

// AddressOf
template <typename T>
typename std::enable_if<std::is_object<T>::value, T*>::type  //
AddressOf(T& arg) noexcept;
template <typename T>
typename std::enable_if<!std::is_object<T>::value, T*>::type  //
AddressOf(T& arg) noexcept;

// Operations on uninitialized memory
//   UninitializedCopy
template <typename InputIt, typename NoThrowForwardIt>
NoThrowForwardIt UninitializedCopy(InputIt first, InputIt last,
                                   NoThrowForwardIt d_first);
//   UninitializedCopyN
template <typename InputIt, typename Size, typename NoThrowForwardIt>
NoThrowForwardIt UninitializedCopyN(InputIt first, Size count,
                                    NoThrowForwardIt d_first);
//   UninitializedFill
template <typename ForwardIt, typename T>
void UninitializedFill(ForwardIt first, ForwardIt last, const T& value);
//   UninitializedFillN
template <typename ForwardIt, typename Size, typename T>
ForwardIt UninitializedFillN(ForwardIt first, Size count, const T& value);
//   UninitializedMove
template <typename InputIt, typename NoThrowForwardIt>
NoThrowForwardIt UninitializedMove(InputIt first, InputIt last,
                                   NoThrowForwardIt d_first);
//   UninitializedMoveN
template <typename InputIt, typename Size, typename NoThrowForwardIt>
std::pair<InputIt, NoThrowForwardIt>  //
UninitializedMoveN(InputIt first, Size count, NoThrowForwardIt d_first);
//   UninitializedDefaultConstruct
template <typename ForwardIt>
void UninitializedDefaultConstruct(ForwardIt first, ForwardIt last);
//   UninitializedDefaultConstructN
template <typename ForwardIt, typename Size>
ForwardIt UninitializedDefaultConstructN(ForwardIt first, Size n);
//   UninitializedValueConstruct
template <typename ForwardIt>
void UninitializedValueConstruct(ForwardIt first, ForwardIt last);
//   UninitializedValueConstructN
template <typename ForwardIt, typename Size>
ForwardIt UninitializedValueConstructN(ForwardIt first, Size n);
//   Destroy
template <typename ForwardIt>
void Destroy(ForwardIt first, ForwardIt last);
//   DestroyN
template <typename ForwardIt, typename Size>
ForwardIt DestroyN(ForwardIt first, Size n);
//   ConstructAt
template <typename T, typename... Args>
constexpr T* ConstructAt(T* p, Args&&... args);
//   DestroyAt
template <typename T>
constexpr void DestroyAt(T* p);

// Include implementation.
#include "algorithm_lite_impl.h"

#endif  // MEMORY_LITE_H