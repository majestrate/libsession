
find_package(PkgConfig REQUIRED)
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS session.proto)
add_library(session
  client.cpp
  cryptography.cpp
  message_base.cpp
  message_parser.cpp
  message_store.cpp
  snode_api.cpp
  swarm.cpp
  ${PROTO_SRCS})

target_include_directories(session PUBLIC ${Protobuf_INCLUDE_DIRS})
target_include_directories(session PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(session PUBLIC ${Protobuf_LIBRARIES} sodium SQLiteCpp onionreq)
