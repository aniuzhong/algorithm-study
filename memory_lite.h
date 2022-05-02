#ifndef MEMORY_LITE_H
#define MEMORY_LITE_H

#include <utility>  // std::pair
//
template <typename ForwardIt, typename Size, typename T>
ForwardIt UninitializedFillN(ForwardIt first, Size count, const T& value);

// Include implementation.
#include "algorithm_lite_impl.h"

#endif  // MEMORY_LITE_H