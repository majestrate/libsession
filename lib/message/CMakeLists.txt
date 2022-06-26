


protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS session.proto)

add_library(session-message
  STATIC
  ${PROTO_SRCS}
  base.cpp
  parser.cpp
  serialize.cpp)

target_include_directories(session-message PRIVATE ${Protobuf_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(session-message PRIVATE ${Protobuf_LIBRARIES})
