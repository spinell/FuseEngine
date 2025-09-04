find_package(GTest 1.17.0 EXACT CONFIG REQUIRED)

add_executable(TestFuseCore
    GtestUtils.cpp
    GtestUtils.h
    TestAngle.cpp
    TestVec3.cpp
    TestVec4.cpp
    TestMat4.cpp
    TestEnumFlags.cpp
    TestEnum.cpp
    TestGetTypeName.cpp
)

fuse_set_compiler_warnings(TestFuseCore)

target_link_libraries(TestFuseCore
    PRIVATE
        GTest::gmock_main
        Fuse::Core
)

add_test(NAME FuseCore COMMAND TestFuseCore)
