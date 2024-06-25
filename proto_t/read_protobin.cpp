#include "Person.pb.h"  
#include <fstream>  
#include <iostream>  
  
int main() {  
    Person person;  
  
    // 从文件读取  
    std::ifstream infile("person_data.bin", std::ios::binary | std::ios::in);  
    if (!infile) {  
        std::cerr << "Failed to open file" << std::endl;  
        return 1;  
    }  
  
    infile.seekg(0, infile.end);  
    int length = infile.tellg();  
    infile.seekg(0, infile.beg);  
  
    char* buffer = new char[length];  
    infile.read(buffer, length);  
    infile.close();  
  
    std::string serialized_data(buffer, length);  
    delete[] buffer;  
  
    // 反序列化  
    if (!person.ParseFromString(serialized_data)) {  
        std::cerr << "Failed to parse person" << std::endl;  
        return 1;  
    }  
  
    // 使用person对象...  
    std::cout << "Name: " << person.name() << std::endl;  
    std::cout << "ID: " << person.id() << std::endl;  
    std::cout << "Email: " << person.email() << std::endl;  
  
    return 0;  
}
