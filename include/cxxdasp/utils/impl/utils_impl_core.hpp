//
//    Copyright (C) 2014 Haruki Hasegawa
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//

#ifndef CXXDASP_UTILS_IMPL_UTILS_IMPL_CORE_HPP_
#define CXXDASP_UTILS_IMPL_UTILS_IMPL_CORE_HPP_

#include <cassert>
#include <cxxporthelper/cstdint>
#include <cxxporthelper/type_traits>
#include <cxxporthelper/compiler.hpp>

// macros

#if (CXXPH_COMPILER_IS_GCC && CXXPH_GCC_VERSION >= 40700) ||                                                           \
    (CXXPH_COMPILER_IS_CLANG && __has_builtin(__builtin_assume_aligned))
#define CXXDASP_UTIL_ASSUME_ALIGNED_FUNC(pointer, alignment)    \
    cxxdasp::utils::typed_pointer_cast_helper((pointer), __builtin_assume_aligned((pointer), alignment))
#else
#define CXXDASP_UTIL_ASSUME_ALIGNED_FUNC(pointer, alignment) (pointer)
#endif

#define CXXDASP_UTIL_ASSUME_ALIGNED(pointer, alignment)                                                                \
    do {                                                                                                               \
        assert(utils::is_aligned((pointer), (alignment)));                                                             \
        pointer = CXXDASP_UTIL_ASSUME_ALIGNED_FUNC((pointer), (alignment));                                              \
    } while (0)

namespace cxxdasp {
namespace utils {

inline bool is_aligned(const void *address, std::size_t alignment) CXXPH_NOEXCEPT
{
    const uintptr_t a = reinterpret_cast<uintptr_t>(address);
    return ((a & (alignment - 1)) == 0);
}

template <typename T>
inline T *typed_pointer_cast_helper(T *unused, void *pointer)
{
    return static_cast<T*>(pointer);
}

//
#if CXXPH_COMPILER_IS_GCC
#define CXXPH_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#define CXXPH_GCC_VERSION 0
#endif

} // namespace utils
} // namespace cxxdasp

#endif // CXXDASP_UTILS_IMPL_UTILS_IMPL_CORE_HPP_
