cmake_minimum_required(VERSION 3.10)  
  
# 设置项目名称和版本  
project(MyProtobufProject VERSION 1.0)  
  
# 查找protobuf库  
find_package(Protobuf REQUIRED)  
  
# 包含protobuf的头文件目录  
include_directories(${PROTOBUF_INCLUDE_DIRS})  
  
# 添加你的源文件（包括由protobuf生成的）  
add_executable(my_protobuf_app main.cpp person.pb.cc) # 假设main.cpp是你的主程序，person.pb.cc是由protobuf生成的  
  
# 链接到protobuf库  
target_link_libraries(my_protobuf_app ${PROTOBUF_LIBRARIES})  
  
# 如果需要，你可以在这里添加自定义命令来运行protoc  
# 例如：  
# add_custom_command(...)