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
  rson new_person;
  ne + -person.ParseFromString(serialized_person);

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



  //转换proto message 为json string
  std::string resp_string;
  google::protobuf::util::JsonPrintOptions json_options;
  json_options.preserve_proto_field_names = true;
  google::protobuf::util::MessageToJsonString(person, &resp_string, json_options);
  std::cout << resp_string << ";"  ;
// 写入txt文件（不使用二进制模式）

  std::ofstream outfile_txt("person_data.txt");
  if (!outfile_txt.is_open()) {
    std::cerr << "Failed to open file for writing: person_data.txt" << std::endl;
    return 1;
  }

  outfile_txt << resp_string ;
  outfile_txt.close();




  return 0;
} +