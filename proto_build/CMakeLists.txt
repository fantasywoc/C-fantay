# 设置CMake的最小版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(myapp)

# Set the path where Protobuf is installed
#set(PROTOBUF_PATH "/media/yb/data/study/C-fantay/proto_t/protobuf")


set(Protobuf_PREFIX_PATH
   ${CMAKE_SOURCE_DIR}/protobuf/include
   ${CMAKE_SOURCE_DIR}/protobuf/lib
   ${CMAKE_SOURCE_DIR}/protobuf/bin
)
list(APPEND CMAKE_PREFIX_PATH "${Protobuf_PREFIX_PATH}")
#include(FindProtobuf)
# 获取protobuf库
find_package(Protobuf REQUIRED)

file(GLOB PROTOFILES  "${CMAKE_SOURCE_DIR}/proto/*.proto")
# 输出找到的.proto文件列表
message(STATUS "Proto files found:")
foreach(protofile ${PROTOFILES})
    message(STATUS "  ${protofile}")
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${protofile})

endforeach()

message(STATUS "  ${PROTO_SRCS}")
message(STATUS "  ${PROTO_HDRS}")
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOFILES})
# message(STATUS "  ${PROTO_SRCS}")
# message(STATUS "  ${PROTO_HDRS}")

add_executable(my_app main.cpp ${PROTO_SRCS} ${PROTO_HDRS})
# Find required protobuf package in the specified path
#find_package(Protobuf REQUIRED PATHS ${PROTOBUF_PATH})
#if(PROTOBUF_FOUND)
#    message(STATUS "protobuf library found")
#else()
#    message(FATAL_ERROR "protobuf library is needed but can't be found")
#endif()

include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS person.proto)


target_link_libraries(my_app ${Protobuf_LIBRARIES})





