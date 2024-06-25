 #远程push新分支
git push --set-upstream origin C++


在C++中使用Protocol Buffers（protobuf）作为数据类型是一种常见做法，尤其是在需要序列化和反序列化数据，以及在不同平台或语言之间交换数据的场景中。Protocol Buffers是Google开发的一种数据序列化协议，它可以将结构化数据序列化为一种紧凑的二进制格式，并支持多种编程语言。

下面是如何在C++中使用protobuf的基本步骤：
 定义.proto文件

首先，你需要定义你的数据结构在.proto文件中。例如，你可以创建一个名为person.proto的文件，内容如下：

```protobuf

syntax = "proto3";  
  
message Person {  
  string name = 1;  
  int32 id = 2;  
  string email = 3;  
  
  enum PhoneType {  
    MOBILE = 0;  
    HOME = 1;  
    WORK = 2;  
  }  
  
  message PhoneNumber {  
    string number = 1;  
    PhoneType type = 2;  
  }  
  
  repeated PhoneNumber phones = 4;  

}
```

  生成C++代码

使用protobuf编译器protoc从.proto文件生成C++代码。你需要安装protobuf并设置环境变量。然后，你可以使用以下命令生成C++代码：

```bash

protoc --cpp_out=. person.proto
```
这将生成person.pb.h和person.pb.cc两个文件。
3. 在C++代码中使用protobuf

在你的C++代码中，包含生成的头文件，并使用protobuf定义的数据类型。例如：

```cpp

#include "person.pb.h"  
  
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
  if (new_person.has_name()) {  
    std::cout << "Name: " << new_person.name() << std::endl;  
  }  
  
  // ... 访问其他字段 ...  
  
  return 0;  

}
```
 编译和运行你的C++代码

确保你的编译器和链接器可以找到protobuf库，并链接到你的代码中。然后，编译并运行你的程序。

注意：以上示例是基于proto3语法的。如果你使用的是proto2，语法和API可能会有所不同。但是，基本的概念和步骤是相似的。