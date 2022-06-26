# message parsing library for hiding the godawful internals of that
add_subdirectory(message)
# network transport layer for abstracting how we send stuff to and from the network
add_subdirectory(transport)
# network state layer for consensus related activities
add_subdirectory(netstate)
# cryptographic implementation details library
add_subdirectory(cryptography)
# for storing message data
add_subdirectory(msgstore)
# lib for storing files locally
add_subdirectory(filestore)
# lib for handling call related shiz
add_subdirectory(voip)
# lib for logging and platform utils
add_subdirectory(platform)

add_library(session
  session-client.cpp)
target_link_libraries(session PUBLIC session-message session-transport session-netstate session-cryptography session-msgstore session-filestore session-voip session-platform)
# for public c api
target_include_directories(session PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../api/include ${CMAKE_CURRENT_SOURCE_DIR})
