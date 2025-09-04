#pragma once

namespace fuse {

template <auto T>
constexpr auto getEnumName() noexcept {
    // Base on from https://ykiko.me/en/articles/680412313/
#if defined(__GNUC__) || defined(__clang__)
    // on GCC/Clang funcName will be line
    // - std::string_view fuse::enum_name() [T = xxx::xxx::kRed]
    // - std::string_view fuse::enum_name() [T = EnumName_EnumName_Test::TestBody()::Color::Red]
    // here were extracting kRed
    const std::string_view funcName  = __PRETTY_FUNCTION__;
    const std::size_t      start     = funcName.find('=') + 2;
    const std::size_t      end       = funcName.size() - 1;
    const std::string_view paramName = std::string_view{funcName.data() + start, end - start};
#elif defined(_MSC_VER)
    // on MSVC funcName will be line
    // - class std::basic_string_view<char,struct std::char_traits<char> > __cdecl fuse::enum_name<EnumName_EnumName_Test::TestBody::kRed>(void)
    // - class std::basic_string_view<char,struct std::char_traits<char> > __cdecl fuse::enum_name<EnumName_EnumName_Test::TestBody::Color::Red>(void)
    // here were extracting kRed
    const std::string_view funcName  = __FUNCSIG__;
    const std::size_t      start     = funcName.find('<') + 1;
    const std::size_t      end       = funcName.rfind(">(");
    const std::string_view paramName = std::string_view{funcName.data() + start, end - start};
#else
#error "Unknown compiler."
#endif
    if (const auto newStart = paramName.rfind("::"); newStart == std::string_view::npos) {
        return paramName;
    } else {
        // extract fromthe last :: to  the end
        return std::string_view{paramName.data() + newStart + 2, paramName.size() - newStart - 2};
    }
}

} // namespace fuse
