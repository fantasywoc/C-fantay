# C++

---

# build g++ 

**动态库和静态库**

在 C++ 中，`.so` 和 `.a` 文件分别代表共享库和静态库。以下是它们的定义和创建方法：

## 静态库(.a 文件)

静态库是编译好的代码集合，在链接时被直接复制到最终的可执行文件中。创建静态库的步骤如下：

1. **编写源代码**：例如 `example.cpp`。

```bash
// example.cpp
#include <iostream>

void hello() {
    std::cout << "Hello from static library!" << std::endl;
}
```

**编译源代码为目标文件**：

```bash
g++ -c example.cpp -o example.o
```

**创建静态库**：

```bash
ar rcs libexample.a example.o
```

**使用静态库**：

在另一个源文件中使用这个静态库：

```c++
// main.cpp
#include <iostream>

extern "C" void hello(); // 声明外部函数

int main() {
    hello();
    return 0;
}
```

编译并链接静态库：

```bash
g++ main.cpp -L. -lexample -o main
```



## 共享库(.so 文件)

共享库在运行时被加载，而不是在编译时。创建共享库的步骤如下：

1. **编写源代码**：同样使用 `example.cpp`。
2. **编译为共享库**：

```bash
g++ -fPIC -shared example.cpp -o libexample.so
```

这里，`-fPIC` 表示生成位置无关的代码，以便可以在不同地址加载。

**使用共享库**：

类似于使用静态库的方式：

```bash
// main.cpp
#include <iostream>

extern "C" void hello();

int main() {
    hello();
    return 0;
}
```

编译并链接共享库：

```bash
g++ main.cpp -L. -lexample -o main
```



## 运行时的库路径

运行使用共享库的程序时，你可能需要确保系统能找到共享库。可以通过设置 `LD_LIBRARY_PATH` 环境变量来指定库的搜索路径：

```bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
```

## 总结

- **静态库**（`.a`）在编译时链接到可执行文件中，增加了可执行文件的大小，但不需要在运行时依赖库文件。
- **共享库**（`.so`）则在运行时动态加载，可以减少可执行文件的大小，并且多个程序可以共享同一库。

# build Cmake

使用 CMake 编译文件为动态库和静态库是非常简单的。下面是如何分别创建动态库和静态库的示例。

## 创建动态库

1. ### **目录结构**：

```c++
my_project/
├── CMakeLists.txt
└── src/
    ├── my_library.cpp
    └── my_library.h
```

**my_library.h**：

```c++
#ifndef MY_LIBRARY_H
#define MY_LIBRARY_H

void hello();

#endif // MY_LIBRARY_H
```

**my_library.cpp**：

```c++
#include <iostream>
#include "my_library.h"

void hello() {
    std::cout << "Hello from the dynamic library!" << std::endl;
}
```

**CMakeLists.txt**：

```bash
cmake_minimum_required(VERSION 3.10)

project(MyLibrary)
# 创建动态库
add_library(my_dynamic_lib SHARED src/my_library.cpp)

# 指定库的头文件路径
target_include_directories(my_dynamic_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
```

**构建项目**：

```bash
mkdir build
cd build
cmake ..
make
```

**结果**： 在 `build` 目录下会生成 `libmy_dynamic_lib.so`（在 Linux 上）或 `my_dynamic_lib.dll`（在 Windows 上）。

## 创建静态库

1. **CMakeLists.txt**（可以在同一文件中，或新建一个）：

```cmake
cmake_minimum_required(VERSION 3.10)

project(MyLibrary)

# 创建静态库
add_library(my_static_lib STATIC src/my_library.cpp)

# 指定库的头文件路径
target_include_directories(my_static_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
```

**构建项目**：

```bash
mkdir build
cd build
cmake ..
make
```

**结果**： 在 `build` 目录下会生成 `libmy_static_lib.a`（在 Linux 上）或 `my_static_lib.lib`（在 Windows 上）。

## 总结

- 创建动态库使用 `SHARED` 关键字。
- 创建静态库使用 `STATIC` 关键字。
- 使用 `target_include_directories` 指定头文件路径，以便其他目标可以使用这些库。

你可以根据需要选择构建动态库或静态库，或者同时构建两者，方法是将相关的 `add_library` 调用放在同一 `CMakeLists.txt` 中。