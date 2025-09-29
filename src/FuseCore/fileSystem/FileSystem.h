#pragma once
#include <expected>
#include <filesystem>
#include <format>
#include <string>
#include <vector>

namespace fuse {

/// @brief Define all file error codes.
enum class FileErrorCode : std::uint8_t {
    FileNotFound,     ///< The file is not found.
    NotAFile,         ///< The file is not a regular file.
    FileTooLarge,     ///< The file is too large to be read.
    ReadFailure,      ///< A error occur while reading a file.
    PermissionDenied, ///< Permission denied for reading/writing file.
    MemoryAllocation, ///< A memory error occur while reading a file.
    Unknown           ///< Any other error not explicitly handled.
};

/// @brief Represents a file error
struct FileError {
    FileErrorCode         errorCode; ///< The error code
    std::filesystem::path path;      ///< The path that has trigger the error.
};

/// @brief Utility functions for file system.
class FileSystem {
public:
    /// @brief Read a file as binary and return it contains in a std::vector.
    ///
    /// @param filename The file to read.
    /// @return The contain od the file or a \p FileError if a error occur.
    static std::expected<std::vector<char>, FileError> ReadFile(
      const std::filesystem::path& filename);

    /// @brief return the path of the executable of the application.
    static std::filesystem::path GetExecutableDirectory();

    /// @brief return the basename of the executable of the application.
    static std::string GetExecutableBaseName();

    /// @return Return the full pathof the application.
    static std::filesystem::path GetExecutablePath();
};

} // namespace fuse

namespace std {


/// @related fuse::FileErrorCode
std::string_view toString(fuse::FileErrorCode ec);

/// @related fuse::FileErrorCode
template <>
struct formatter<fuse::FileErrorCode> {

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const fuse::FileErrorCode& errorCode, FormatContext& ctx) const {
        return format_to(ctx.out(), "{}", toString(errorCode));
    }
};

} // namespace std

namespace fuse {

/// @related FileError
std::ostream& operator<<(std::ostream& stream, const FileError& error);

} // namespace fuse
