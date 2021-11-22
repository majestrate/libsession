cmake_minimum_required(VERSION 3.10)  # bionic's cmake version

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Has to be set before `project()`, and ignored on non-macos:
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.12 CACHE STRING "macOS deployment target (Apple clang only)")

set(LANGS CXX)
if(APPLE)
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
    DESCRIPTION "libession session - C++ implementation of session protocol"
    LANGUAGES ${LANGS})

include(CheckCXXSourceCompiles)
include(CheckLibraryExists)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external)

find_package(PkgConfig REQUIRED)
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS session/session.proto)
add_library(session
  session/client.cpp
  session/cryptography.cpp
  session/message_base.cpp
  session/message_parser.cpp
  session/message_store.cpp
  session/snode_api.cpp
  session/swarm.cpp
  ${PROTO_SRCS})

target_include_directories(session PUBLIC ${Protobuf_INCLUDE_DIRS})
target_include_directories(session PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(session PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(session PUBLIC ${Protobuf_LIBRARIES} sodium SQLiteCpp onionreq)

add_executable(session-cli cli/main.cpp)
target_link_libraries(session-cli PUBLIC session)
