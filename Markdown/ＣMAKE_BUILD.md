CMAKE　BUILD

## Cmake 

### Project 目录结构

```shell
Cmake_buils_project/
├── build
├── CMakeLists.txt
├── functions
│   ├── CMakeLists.txt
│   ├── function.cpp
│   └── function.h
└── main.cpp

```

functions/CMakeLists.txt

```cmake
#递归将本文件夹下所有cpp放到FUNCTIONS中
file(GLOB_RECURSE FUNCTIONS ./ *.cpp)

#将FUNCS中所有cpp编译为funcs这个lib库
# add_library(funcs   ${FUNCTIONS} )

# 编译静态库
# add_library(funcs STATIC  ${FUNCTIONS}  )

# 编译动态库
add_library(funcs  SHARED  ${FUNCTIONS} )

# 设置库的包含目录
target_include_directories(funcs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```

CMakeLists.txt

```cmake
#需求的最低cmake程序版本
cmake_minimum_required(VERSION 3.12)

#本工程的名字
project(OpenGL )

#本工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)

#将funcs文件夹纳入到编译系统
add_subdirectory(functions)
##add_subdirectory(functions1)
#搜索所有的cpp，加入SRCS变量中
aux_source_directory(. SRCS)

#本工程所有cpp文件编译链接，生成exe
add_executable(glStudy  ${SRCS})

#将funcs.lib链接入softRender
target_link_libraries(glStudy funcs)
```



functions/function.cpp

```cpp
#include "function.h"
#include<iostream>
void myFunction() {
    // 静态局部变量，只在第一次调用函数时初始化
    static bool isFirstCall = true;
    if (isFirstCall) {
        std::cout << "这是第一次调用函数！" << "  ------------->isFirstCall:" << isFirstCall << std::endl;
        // 在这里可以进行一些只在第一次调用时需要执行的初始化操作
        // 更改isFirstCall的值，以便在下一次调用时不会再次进入这个if语句块
        isFirstCall = false;
    } else {
        std::cout << "这不是第一次调用函数。" << "isFirstCall:" << isFirstCall << std::endl;
    }
}
void test_static() {
    myFunction();
}
```

functions/function.h

```c++
#pragma once
#include<iostream>
void myFunction();
void test_static();
```

main.cpp

```c++
#include<iostream>
#include"./functions/function.h"
int main(){
    test_static();
    test_static();
}
```

Linux 编译

```shell
mkdir -p build && cd build && cmake .. && make 
```

Windows 编译

```shell
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=g++ ..
```





## Linux

在 Linux 中，您可以通过多种方式在 shell 中导入 `.so`（共享对象）库。以下是一些常见的方法。

### 1. 使用 `LD_LIBRARY_PATH` 环境变量

您可以通过设置 `LD_LIBRARY_PATH` 环境变量来指定共享库的搜索路径。例如：

```bash
export LD_LIBRARY_PATH=/path/to/your/lib:$LD_LIBRARY_PATH
```

在这条命令中，将 `/path/to/your/lib` 替换为您的 `.so` 文件所在的目录。然后，您可以运行需要该库的可执行文件。

### 2. 使用 `ldconfig`

如果您希望系统在启动时加载库，可以将 `.so` 文件复制到 `/usr/lib` 或 `/usr/local/lib` 目录，然后运行 `ldconfig`：

```bash
sudo cp yourlib.so /usr/local/lib
sudo ldconfig
```

### 3. 使用 `gcc` 编译时链接

如果您在编译一个 C 或 C++ 程序时想要链接共享库，可以使用 `-l` 选项。例如：

```shell
gcc -o myprogram myprogram.c -L/path/to/your/lib -lyourlib
```

这里，`-L` 指定库的路径，`-l` 指定库的名称（不带前缀 `lib` 和后缀 `.so`）。

### 4. 使用 `dlopen()` 动态加载

如果您希望在运行时动态加载共享库，可以使用 `dlopen()` 函数。以下是一个示例代码片段：

```c
#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle;
    handle = dlopen("libyourlib.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    // 使用库中的函数...
    
    dlclose(handle);
    return 0;
}
```

### 5. 运行时链接器

您也可以在运行程序时指定共享库的路径。例如：

```shell
./myprogram -rpath=/path/to/your/lib
```