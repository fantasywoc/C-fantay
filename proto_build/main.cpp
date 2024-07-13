#include "person.pb.h"

#include <fstream>
#include<string>

#include <iostream>
#include <google/protobuf/util/json_util.h>

int main() {
  // 创建一个新的Person对象
  Person person;
  person.set_name("Alice");
  person.set_id(1234);
  person.set_email("alice@example.com");

  // 添加电话号码
  Person::PhoneNumber* phone = person.add_phones();
  phone->set_number("555-4321");
  phone->set_type(Person::HOME);

  // 序列化Person对象到字符串
  std::string serialized_person;
  person.SerializeToString(&serialized_person);

  // ... 在这里，你可以将serialized_person发送到另一个系统或存储它 ...

  // 反序列化字符串回到Person对象
  Person new_person;
  new_person.ParseFromString(serialized_person);

  // 验证反序列化是否成功，并访问数据
  if (new_person.name().empty()) {
    std::cout << "Name: " << new_person.name() << std::endl;
  }

  // ... 访问其他字段 ...


  // 序列化
  std::string serialized_data;
  person.SerializeToString(&serialized_data);

  // 写入二进制文件
  std::ofstream outfile("person_data.bin", std::ios::binary);
  if (!outfile.write(serialized_data.data(), serialized_data.size())) {
    std::cerr << "Failed to write file" << std::endl;
    return 1;
  }
  outfile.close();




  Person person_serialized;
// 从文件读取
  std::ifstream infile("person_data.bin", std::ios::binary | std::ios::in); // 打开文件以二进制读取模式
  if (!infile) { // 检查文件是否成功打开
    std::cerr << "Failed to open file" << std::endl; // 如果文件打开失败，输出错误信息
    return 1; // 并返回1表示程序异常退出
  }

  // 获取文件大小
  infile.seekg(0, infile.end); // 将文件指针移动到文件末尾
  std::streamsize length = infile.tellg(); // 获取当前文件指针位置（即文件大小）
  infile.seekg(0, infile.beg); // 将文件指针移回文件开头

  // 读取文件内容到向量中
  std::vector<char> buffer(length); // 创建一个字符向量，大小等于文件大小
  if (!infile.read(buffer.data(), length) || infile.gcount() != length) { // 尝试读取文件内容
    // 如果读取失败或读取的字节数不等于文件大小
    std::cerr << "Failed to read file contents" << std::endl; // 输出错误信息
    infile.close(); // 关闭文件（尽管在这里关闭可能不是必须的，因为析构函数会负责）
    return 1; // 并返回1表示程序异常退出
  }
  infile.close(); // 明确关闭文件，这是一个好习惯

  // 将向量内容转换为字符串
  std::string serialized_data1(buffer.begin(), buffer.end()); // 使用向量的迭代器来初始化字符串

  // 反序列化
  if (!person_serialized.ParseFromString(serialized_data1)) { // 尝试从字符串中解析Person对象
    std::cerr << "Failed to parse person" << std::endl; // 如果解析失败，输出错误信息
    return 1; // 并返回1表示程序异常退出
  }









  person_serialized.set_name("person_serialized");
  //转换proto message 为json string
  std::string resp_string;
  google::protobuf::util::JsonPrintOptions json_options;
  json_options.preserve_proto_field_names = true;
  google::protobuf::util::MessageToJsonString(person_serialized, &resp_string, json_options);
  std::cout << resp_string << std::endl  ;
// 写入txt文件（不使用二进制模式）

  std::ofstream outfile_txt("person_data.txt");
  if (!outfile_txt.is_open()) {
    std::cerr << "Failed to open file for writing: person_data.txt" << std::endl;
    return 1;
  }
  outfile_txt << resp_string ;
  outfile_txt.close();




  return 0;
}