# 设置CMake的最小版本要求  
cmake_minimum_required(VERSION 3.10)  
  
# 设置项目名称  
project(MyProject)  
  
# 设置C++标准  
set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
  
# 设置protobuf的头文件和库文件路径  
set(PROTOBUF_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/include)  
set(PROTOBUF_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/lib/libprotobuf.so)  
# 注意：如果protobuf需要其他库（如libprotoc），你可能需要添加它们  
# 例如：set(PROTOBUF_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/lib/libprotobuf.so ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/lib/libprotoc.so)  
  
# 添加protobuf的头文件搜索路径  
include_directories(${PROTOBUF_INCLUDE_DIRS})  
  
# 假设你有一个由protobuf生成的源文件 persion.pb.cc  
# 添加源文件到可执行文件或库  
add_executable(my_program persion.pb.cc persion.cpp read_protobin.cpp)  
  
# 链接到protobuf库  
target_link_libraries(my_program ${PROTOBUF_LIBRARIES})  
  
# 如果protobuf的.proto文件需要由protoc编译器生成.pb.cc和.pb.h，  
# 你可以使用add_custom_command或add_custom_target来配置这一步  
# 这里是一个示例，展示如何添加自定义命令来生成protobuf文件  
add_custom_command(  
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/persion.pb.cc ${CMAKE_CURRENT_BINARY_DIR}/persion.pb.h  
  COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} --cpp_out=${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/persion.proto  
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/persion.proto  
  COMMENT "Running Protocol Buffers compiler on persion.proto"  
  VERBATIM  
)  
  
# 添加生成的源文件到目标，确保在add_executable之后  
add_dependencies(my_program persion_proto_gen)  
# 创建一个虚拟目标来管理protoc的生成  
add_custom_target(persion_proto_gen ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/persion.pb.cc ${CMAKE_CURRENT_BINARY_DIR}/persion.pb.h)  
  
# 如果你的项目包含多个目录，使用add_subdirectory来包含它们  
# add_subdirectory(src)  
  
# 其他CMake配置...  
  
# 如果需要安装可执行文件或库，可以添加install命令  
install(TARGETS my_program DESTINATION bin)