# FuseEngine
C++ GameEngine with Editor for leaning

## Compiler
- Windows
  - cl.exe: Build pass
  - clang.exe: Build pass
  - clang-cl.exe: Build pass 

- Linux
  - Gcc13: Build pass
  - Gcc14: Build pass
  - Clang18 (Gcc14 header): Build Fail `std::expected` 
  - Clang19 (Gcc14 header): Build pass
  - Clang20 (Gcc14 header): Build pass

## TODO

- VCPKG: Install gtest only when building tests.
