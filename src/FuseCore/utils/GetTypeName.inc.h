#pragma once
#include "TypeTraits.h"

namespace fuse {

template <class T>
constexpr auto getTypeFullName() noexcept {
    // note: clang define __GNUC__ on linux
    // note: clang define _MSC_VER on windows
#if defined(__clang__)
    // If this function return auto __PRETTY_FUNCTION__ look like
    //   auto fuse::getTypeFullName() [T = Toto]
    //   auto fuse::getTypeFullName() [T = ns::Toto]
    //   auto fuse::getTypeFullName() [T = std::vector<int>]
    // If this function return std::string_view __PRETTY_FUNCTION__ look like
    //   std::string_view fuse::getTypeFullName() [T = Toto]
    //   std::string_view fuse::getTypeFullName() [T = ns::Toto]
    //   std::string_view fuse::getTypeFullName() [T = std::vector<int>]
    const auto funcName  = std::string_view(__PRETTY_FUNCTION__);
    const auto start     = funcName.find('=') + 2; // position where the paramater name start
    const auto end       = funcName.size() - 1;    // position where the paramater name end
    const auto paramName = funcName.substr(start, end - start);
    return paramName;
#elif defined(__GNUC__)
    // If this function return auto __PRETTY_FUNCTION__ look like
    //   auto fuse::getTypeFullName() [T = Toto]
    //   auto fuse::getTypeFullName() [T = ns::Toto]
    //   auto fuse::getTypeFullName() [T = std::vector<int>]
    // If this function return std::string_view __PRETTY_FUNCTION__ look like
    //   constexpr std::string_view fuse::getTypeFullName() [with T = Toto; std::string_view = std::basic_string_view<char>]
    //   constexpr std::string_view fuse::getTypeFullName() [with T = ns::Toto; std::string_view = std::basic_string_view<char>]
    //   constexpr std::string_view fuse::getTypeFullName() [with T = std::vector<int>; std::string_view = std::basic_string_view<char>]
    const auto funcName  = std::string_view(__PRETTY_FUNCTION__);
    const auto start     = funcName.find('=') + 2; // position where the paramater name start
    const auto end       = funcName.size() - 1;    // position where the paramater name end
    const auto paramName = funcName.substr(start, end - start);

    return paramName;
#elif defined(_MSC_VER)
    // on MSVC funcName will be line
    // - class std::basic_string_view<char,struct std::char_traits<char> > __cdecl fuse::enum_name<EnumName_EnumName_Test::TestBody::kRed>(void)
    // - class std::basic_string_view<char,struct std::char_traits<char> > __cdecl fuse::enum_name<EnumName_EnumName_Test::TestBody::Color::Red>(void)
    // here were extracting kRed
    const auto funcName  = std::string_view(__FUNCSIG__);
    const auto start     = funcName.find('<') + 1;
    const auto end       = funcName.rfind(">(");
    const auto paramName = funcName.substr(start, end - start);
    return paramName;
#else
#error "Unknown compiler."
    return {};
#endif
}

template <class T>
constexpr auto getTypeName() noexcept {
    // Note: remove reference first
    using Type = fuse::remove_all_pointers_t<std::remove_cvref_t<T>>;
    return getTypeFullName<Type>();
}

} // namespace fuse
