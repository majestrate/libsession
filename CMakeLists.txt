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
    DESCRIPTION "libsession session - C++ implementation of session protocol"
    LANGUAGES ${LANGS})

include(CheckCXXSourceCompiles)
include(CheckLibraryExists)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external)

find_package(PkgConfig REQUIRED)
find_package(Protobuf REQUIRED)
find_package(spdlog REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS session/session.proto)

add_library(session-message
  STATIC
  ${PROTO_SRCS}
  session/message/base.cpp
  session/message/parser.cpp
  session/message/serialize.cpp)

add_library(session
  session/client.cpp
  session/cryptography.cpp
  session/message_store.cpp
  session/snode_api.cpp
  session/swarm.cpp)


target_include_directories(session-message PRIVATE ${Protobuf_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(session-message PRIVATE ${Protobuf_LIBRARIES})
target_include_directories(session PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(session PUBLIC session-message sodium SQLiteCpp onionreq CLI11::CLI11 spdlog::spdlog)

add_executable(session-cli cli/main.cpp)
target_link_libraries(session-cli PUBLIC session)
