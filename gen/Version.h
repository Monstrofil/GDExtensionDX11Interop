#pragma once
// This file is generated by cmake. Changes will be overwritten.
// clang-format off

#include <string_view>

// Creates a version number for use in macro comparisons.
//
// Example:
//
// // Check if the version is less than 2.1.0
// #if GDDX11INTEROPDEMO_VERSION < GDDX11INTEROPDEMO_VERSION_CHECK(2, 1, 0)
//     // do stuff
// #endif
//
// Returns an integer which may be used in comparisons
#define GDDX11INTEROPDEMO_VERSION_CHECK( major, minor, patch ) ( ((major)<<16) | ((minor)<<8) | (patch) )

#define GDDX11INTEROPDEMO_VERSION_MAJOR  0
#define GDDX11INTEROPDEMO_VERSION_MINOR  1
#define GDDX11INTEROPDEMO_VERSION_PATCH  0

// The version number of this extension. Used for #if comparisons.
// This is generated using the version set in the CMake project macro.
#define GDDX11INTEROPDEMO_VERSION  GDDX11INTEROPDEMO_VERSION_CHECK( 0, 1, 0 )

namespace VersionInfo {
    // Project name and version as a string.
    // This is generated using the project name from the cmake project macro and the current git commit information.
    //
    // It uses the form "<project name> <last tag>-<# commits since last tag>-<short commit hash>".
    // If there are no commits since the last tag, only the tag is shown.
    constexpr std::string_view VERSION_STR = "GDDx11InteropDemo f2e15b3";

    // The version information as a string.
    // This is generated using the current git commit information.
    //
    // It uses the form "<last tag>-<# commits since last tag>-<short commit hash>".
    // If there are no commits since the last tag, only the tag is shown.
    constexpr std::string_view VERSION_SHORT_STR = "f2e15b3";

    // The full git SHA1 hash as a string.
    // This is generated using the current git commit information.
    constexpr std::string_view GIT_SHA1_STR = "f2e15b3dcff4d70e7f03bf47937b1d68caf218ee";
}
