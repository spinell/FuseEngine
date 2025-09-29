#include "FileSystem.h"

#include <fstream>

#ifdef FUSE_PLATFORM_WINDOWS
#include <Windows.h> // For GetModuleFileName
#elifdef FUSE_PLATFORM_LINUX
#include <unistd.h> // For GetModuleFileName
#elifdef FUSE_PLATFORM_OSX
#include <mach-o/dyld.h> // For _NSGetExecutablePath
#endif

namespace fuse {


std::filesystem::path FileSystem::GetExecutablePath() {
#ifdef FUSE_PLATFORM_WINDOWS
    char buffer[MAX_PATH];
    GetModuleFileName(nullptr, buffer, MAX_PATH);
    return std::string(buffer);
#elif defined(FUSE_PLATFORM_LINUX)
    char          path[FILENAME_MAX];
    const ssize_t count = readlink("/proc/self/exe", static_cast<char*>(path), FILENAME_MAX);
    return {
      std::string(static_cast<char*>(path), (count > 0l) ? static_cast<std::size_t>(count) : 0ul)};
#else
#error "GetExecutablePath() is undefined for this platform !"
#endif
}

std::filesystem::path FileSystem::GetExecutableDirectory() {
    return GetExecutablePath().parent_path();
}

std::string FileSystem::GetExecutableBaseName() { return GetExecutablePath().filename().string(); }

std::expected<std::vector<char>, FileError> FileSystem::ReadFile(
  const std::filesystem::path& filename) {
    std::error_code   errorCode;
    std::vector<char> data;

    if (!std::filesystem::exists(filename, errorCode)) {
        return std::unexpected(
          FileError{.errorCode = FileErrorCode::FileNotFound, .path = filename});
    }

    if (!std::filesystem::is_regular_file(filename)) {
        return std::unexpected(FileError{.errorCode = FileErrorCode::NotAFile, .path = filename});
    }

    const uintmax_t fileSize = std::filesystem::file_size(filename);
    if (fileSize > std::numeric_limits<uintmax_t>::max()) {
        return std::unexpected(
          FileError{.errorCode = FileErrorCode::FileTooLarge, .path = filename});
    }

    // if we can't open the file, assume it a permission access error
    // because we already have check if the file exists and it a regular file.
    std::ifstream ifs(filename.string(), std::ios::binary);
    if (!ifs) {
        return std::unexpected(
          FileError{.errorCode = FileErrorCode::PermissionDenied, .path = filename});
    }

    //try {
    data.resize(fileSize);
    //} catch (std::bad_alloc& /*ex*/) {
    ifs.close();
    return std::unexpected(
      FileError{.errorCode = FileErrorCode::MemoryAllocation, .path = filename});
    //}

    // fileSize is casted to std::streamsize, this is save because we already have checked
    // that the size is not bigger than  std::numeric_limits<std::streamsize>::max().
    if (!ifs.read(data.data(), static_cast<std::streamsize>(fileSize))) {
        ifs.close();
        return std::unexpected(
          FileError{.errorCode = FileErrorCode::ReadFailure, .path = filename});
    }

    ifs.close();

    return data;
}

std::ostream& operator<<(std::ostream& stream, const FileError& error) {
    switch (error.errorCode) {
        case FileErrorCode::FileNotFound:
            stream << std::format("{} not found.", error.path.string());
            break;
        case FileErrorCode::NotAFile:
            stream << std::format("{} is not a file.", error.path.string());
            break;
        case FileErrorCode::FileTooLarge:
            stream << std::format("{} is to large.", error.path.string());
            break;
        case FileErrorCode::ReadFailure:
            stream << std::format("Failed to read {}.", error.path.string());
            break;
        case FileErrorCode::PermissionDenied:
            stream << std::format("Permission denied: {}.", error.path.string());
            break;
        case FileErrorCode::MemoryAllocation:
            stream << std::format("Memory allocation occurred while reading: {}.",
                                  error.path.string());
            break;
        case FileErrorCode::Unknown:
        default:
            stream << std::format("Unknown error occurred while reading {}.", error.path.string());
            break;
    }
    return stream;
}

} // namespace fuse

namespace std {

string_view toString(fuse::FileErrorCode ec) {
    // clang-format off
    switch (ec) {
        case fuse::FileErrorCode::FileNotFound:     return "FileNotFound";
        case fuse::FileErrorCode::NotAFile:         return "NotAFile";
        case fuse::FileErrorCode::FileTooLarge:     return "FileTooLarge";
        case fuse::FileErrorCode::ReadFailure:      return "ReadFailed";
        case fuse::FileErrorCode::PermissionDenied: return "PermissionDenied";
        case fuse::FileErrorCode::MemoryAllocation: return "MemoryAllocation";
        case fuse::FileErrorCode::Unknown:
        default:                                    return "Unknown";
    }
    // clang-format on
}

} // namespace std
