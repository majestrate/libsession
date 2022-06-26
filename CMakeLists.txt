cmake_minimum_required(VERSION 3.18)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LANGS CXX)
if(APPLE)
  # Has to be set before `project()`, and ignored on non-macos:
  set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14 CACHE STRING "macOS deployment target (Apple clang only)")
  set(LANGS ${LANGS} OBJC)
endif()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  foreach(lang ${LANGS})
    if(NOT DEFINED CMAKE_${lang}_COMPILER_LAUNCHER AND NOT CMAKE_${lang}_COMPILER MATCHES ".*/ccache")
      message(STATUS "Enabling ccache for ${lang}")
      set(CMAKE_${lang}_COMPILER_LAUNCHER ${CCACHE_PROGRAM} CACHE STRING "")
    endif()
  endforeach()
endif()


project(libsession
    VERSION 0.0.1
    DESCRIPTION "libsession - C++ implementation of session protocol"
    LANGUAGES ${LANGS})

include(CheckCXXSourceCompiles)
include(CheckLibraryExists)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Protobuf REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(external)
add_subdirectory(lib)

add_executable(session-cli cli/main.cpp)
target_link_libraries(session-cli PUBLIC session CLI11::CLI11 spdlog::spdlog fmt::fmt)
