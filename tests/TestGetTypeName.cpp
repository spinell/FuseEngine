#include <FuseCore/utils/GetTypeName.h>

#include <gtest/gtest.h>

// clang-format off
class Toto {};
struct Foo {};
union Bar {};
enum UnScopedEnum : std::uint8_t { kRed = 0, kGreen = 1, kBlue = 2 };
enum class ScopedEnum : std::uint8_t { Red = 0, Green = 1, Blue = 2 };
// clang-format on

// clang-format off
namespace ns {

class Toto {};
struct Foo {};
union Bar {};
enum UnScopedEnum : std::uint8_t { kRed = 0, kGreen = 1, kBlue = 2 };
enum class ScopedEnum : std::uint8_t { Red = 0, Green = 1, Blue = 2 };

// clang-format on

} // namespace ns

// test getTypeFullName<class T>
TEST(getTypeFullName, Static) {
    using namespace std::literals;

    // build-in type
    EXPECT_EQ(fuse::getTypeFullName<void>(), "void"sv);
    EXPECT_EQ(fuse::getTypeFullName<int>(), "int"sv);
    EXPECT_EQ(fuse::getTypeFullName<unsigned>(), "unsigned int"sv);
#if defined(__GNUC__) && !defined(__clang__)
    EXPECT_EQ(fuse::getTypeFullName<short>(), "short int"sv);
    EXPECT_EQ(fuse::getTypeFullName<unsigned short>(), "short unsigned int"sv);
    EXPECT_EQ(fuse::getTypeFullName<long>(), "long int"sv);
#else
    EXPECT_EQ(fuse::getTypeFullName<long>(), "long"sv);
#endif
    EXPECT_EQ(fuse::getTypeFullName<float>(), "float"sv);
    EXPECT_EQ(fuse::getTypeFullName<double>(), "double"sv);

#if __GNUC__ || __clang__
    EXPECT_EQ(fuse::getTypeFullName<Toto>(), "Toto"sv);
    EXPECT_EQ(fuse::getTypeFullName<ns::Toto>(), "ns::Toto"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeFullName<Bar>(), "Bar"sv);
    EXPECT_EQ(fuse::getTypeFullName<UnScopedEnum>(), "UnScopedEnum"sv);
    EXPECT_EQ(fuse::getTypeFullName<ScopedEnum>(), "ScopedEnum"sv);
#elif _MSC_VER
    EXPECT_EQ(fuse::getTypeFullName<Toto>(), "class Toto"sv);
    EXPECT_EQ(fuse::getTypeFullName<ns::Toto>(), "class ns::Toto"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeFullName<Bar>(), "union Bar"sv);
    EXPECT_EQ(fuse::getTypeFullName<UnScopedEnum>(), "enum UnScopedEnum"sv);
    EXPECT_EQ(fuse::getTypeFullName<ScopedEnum>(), "enum ScopedEnum"sv);
#endif
    // qualifier
#if __GNUC__ || __clang__
    EXPECT_EQ(fuse::getTypeFullName<const Foo>(), "const Foo"sv);
    EXPECT_EQ(fuse::getTypeFullName<volatile Foo>(), "volatile Foo"sv);
    EXPECT_EQ(fuse::getTypeFullName<const volatile Foo>(), "const volatile Foo"sv);
    EXPECT_EQ(fuse::getTypeFullName<volatile const Foo>(), "const volatile Foo"sv);
#elif _MSC_VER
    EXPECT_EQ(fuse::getTypeFullName<const Foo>(), "const struct Foo"sv);
    EXPECT_EQ(fuse::getTypeFullName<volatile Foo>(), "volatile struct Foo"sv);
    EXPECT_EQ(fuse::getTypeFullName<const volatile Foo>(), "volatile const struct Foo"sv);
    EXPECT_EQ(fuse::getTypeFullName<volatile const Foo>(), "volatile const struct Foo"sv);
#endif
    //
    // pointer
    //
#if __clang__
    EXPECT_EQ(fuse::getTypeFullName<Foo*>(), "Foo *"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo**>(), "Foo **"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const>(), "Foo *const"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const*>(), "Foo *const *"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const* const>(), "Foo *const *const"sv);
#elif __GNUC__
    EXPECT_EQ(fuse::getTypeFullName<Foo*>(), "Foo*"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo**>(), "Foo**"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const>(), "Foo* const"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const*>(), "Foo* const*"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const* const>(), "Foo* const* const"sv);
#elif _MSC_VER
    EXPECT_EQ(fuse::getTypeFullName<Foo*>(), "struct Foo*"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo**>(), "struct Foo**"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const>(), "struct Foo*const "sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const*>(), "struct Foo*const *"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const* const>(), "struct Foo*const *const "sv);
#endif

    // ref
#if __clang__
    EXPECT_EQ(fuse::getTypeFullName<Foo&>(), "Foo &"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo*&>(), "Foo *&"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo**&>(), "Foo **&"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const* const** const&>(), "Foo *const *const **const &"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo&&>(), "Foo &&"sv);
#elif __GNUC__
    EXPECT_EQ(fuse::getTypeFullName<Foo&>(), "Foo&"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo*&>(), "Foo*&"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo**&>(), "Foo**&"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const* const** const&>(), "Foo* const* const** const&"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo&&>(), "Foo&&"sv);
#elif _MSC_VER
    EXPECT_EQ(fuse::getTypeFullName<Foo&>(), "struct Foo&"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo*&>(), "struct Foo*&"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo**&>(), "struct Foo**&"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo* const* const** const&>(),
              "struct Foo*const *const **const &"sv);
    EXPECT_EQ(fuse::getTypeFullName<Foo&&>(), "struct Foo&&"sv);
#endif

#if __clang__ || __GNUC__
    EXPECT_EQ(fuse::getTypeFullName<std::vector<int>>(), "std::vector<int>"sv);
    EXPECT_EQ(fuse::getTypeFullName<std::vector<Foo>>(), "std::vector<Foo>"sv);
#elif _MSC_VER
    EXPECT_EQ(fuse::getTypeFullName<std::vector<int>>(),
              "class std::vector<int,class std::allocator<int> >"sv);
    EXPECT_EQ(fuse::getTypeFullName<std::vector<Foo>>(),
              "class std::vector<struct Foo,class std::allocator<struct Foo> >"sv);
#endif
}

TEST(getTypeName, Static) {
    using namespace std::literals;

    // build-in type
    EXPECT_EQ(fuse::getTypeName<void>(), "void"sv);
    EXPECT_EQ(fuse::getTypeName<int>(), "int"sv);
    EXPECT_EQ(fuse::getTypeName<unsigned>(), "unsigned int"sv);

#if __clang__
    EXPECT_EQ(fuse::getTypeName<long>(), "long"sv);
#elif __GNU__
    EXPECT_EQ(fuse::getTypeName<short>(), "short int"sv);
    EXPECT_EQ(fuse::getTypeName<unsigned short>(), "short unsigned int"sv);
    EXPECT_EQ(fuse::getTypeName<long>(), "long int"sv);
#elif _MSC_VER
    EXPECT_EQ(fuse::getTypeName<short>(), "short"sv);
    EXPECT_EQ(fuse::getTypeName<unsigned short>(), "unsigned short"sv);
    EXPECT_EQ(fuse::getTypeName<long>(), "long"sv);
#endif

    EXPECT_EQ(fuse::getTypeName<float>(), "float"sv);
    EXPECT_EQ(fuse::getTypeName<double>(), "double"sv);

#if __GNUC__ || __clang__
    EXPECT_EQ(fuse::getTypeName<Toto>(), "Toto"sv);
    EXPECT_EQ(fuse::getTypeName<ns::Toto>(), "ns::Toto"sv);
    EXPECT_EQ(fuse::getTypeName<Foo>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Bar>(), "Bar"sv);
    EXPECT_EQ(fuse::getTypeName<UnScopedEnum>(), "UnScopedEnum"sv);
    EXPECT_EQ(fuse::getTypeName<ScopedEnum>(), "ScopedEnum"sv);
#elif _MSC_VER
    EXPECT_EQ(fuse::getTypeName<Toto>(), "class Toto"sv);
    EXPECT_EQ(fuse::getTypeName<ns::Toto>(), "class ns::Toto"sv);
    EXPECT_EQ(fuse::getTypeName<Foo>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Bar>(), "union Bar"sv);
    EXPECT_EQ(fuse::getTypeName<UnScopedEnum>(), "enum UnScopedEnum"sv);
    EXPECT_EQ(fuse::getTypeName<ScopedEnum>(), "enum ScopedEnum"sv);
#endif

    //
    // qualifier
    //
#if __GNUC__ || __clang__
    EXPECT_EQ(fuse::getTypeName<const Foo>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<volatile Foo>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<const volatile Foo>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<volatile const Foo>(), "Foo"sv);
#elif _MSC_VER
    EXPECT_EQ(fuse::getTypeName<const Foo>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<volatile Foo>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<const volatile Foo>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<volatile const Foo>(), "struct Foo"sv);
#endif

    //
    // pointer
    //
#if __clang__ || __GNUC__
    EXPECT_EQ(fuse::getTypeName<Foo*>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo**>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo* const>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo* const*>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo* const* const>(), "Foo"sv);
#elif _MSC_VER
    EXPECT_EQ(fuse::getTypeName<Foo*>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo**>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo* const>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo* const*>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo* const* const>(), "struct Foo"sv);
#endif

    //
    // ref
    //
#if __clang__ || __GNUC__
    EXPECT_EQ(fuse::getTypeName<Foo&>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo*&>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo**&>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo* const* const** const&>(), "Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo&&>(), "Foo"sv);
#elif _MSC_VER
    EXPECT_EQ(fuse::getTypeName<Foo&>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo*&>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo**&>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo* const* const** const&>(), "struct Foo"sv);
    EXPECT_EQ(fuse::getTypeName<Foo&&>(), "struct Foo"sv);
#endif

#if __clang__ || __GNUC__
    EXPECT_EQ(fuse::getTypeName<std::vector<int>>(), "std::vector<int>"sv);
    EXPECT_EQ(fuse::getTypeName<std::vector<Foo>>(), "std::vector<Foo>"sv);
#elif _MSC_VER
    EXPECT_EQ(fuse::getTypeFullName<std::vector<int>>(),
              "class std::vector<int,class std::allocator<int> >"sv);
    EXPECT_EQ(fuse::getTypeFullName<std::vector<Foo>>(),
              "class std::vector<struct Foo,class std::allocator<struct Foo> >"sv);
#endif
}
