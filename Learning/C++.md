# C++

---

# build g++ 

---

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



# Lambda

---

c++11引入了Lambda表达式，使得开发人员可以更方便的创建匿名函数。Lambda表达式是c++语言的一个重要特性，它可以作为函数对象使用，可以用来替代一些繁琐的函数声明和定义。

## **Lambda表达式的语法**

Lambda表达式的基本语法结构如下：

```C++
[capture list] (parameter list) specifiers exception -> type { function body }
```

- [capture list]是捕获列表，在应用中必填。
- (parameter list)是参数列表，在应用中选填。
- specifiers是限定符，在应用中选填。
- exception是异常说明符，在应用中选填。
- -> type是返回值类型，在应用中选填。
- { function body }是表达式的函数体，在应用中必填。

下面是一个简单的Lambda表达式：

```c++
[](int x, int y){ return x + y; }
```

这个Lambda表达式可以看作是一个没有函数名的函数，接受两个整型参数，并返回它们的和。应用实例如下：

```C++
auto f = [](int x, int y){ return x + y; };
int result = f(10, 20);    //result == 30
```

##  Lambda表达式参数详解

### Lambda捕获列表

Lambda表达式与普通函数最大的区别是，除了可以使用参数以外，Lambda函数还可以通过捕获列表访问一些上下文中的数据。具体地，捕捉列表描述了上下文中哪些数据可以被Lambda使用，以及使用方式（以值传递的方式或引用传递的方式）。语法上，在“[]”包括起来的是捕获列表，捕获列表由多个捕获项组成，并以逗号分隔。捕获列表有以下几种形式：

[]表示不捕获任何变量

```C++
auto function = ([]{
		std::cout << "Hello World!" << std::endl;
	}
);

function();
```

### [var]

表示值传递方式捕获变量var

```C++
int num = 100;
auto function = ([num]{
		std::cout << num << std::endl;
	}
);

function();
```

### [=]

表示值传递方式捕获所有父作用域的变量（包括this）

```C++
int index = 1;
int num = 100;
auto function = ([=]{
			std::cout << "index: "<< index << ", " 
                << "num: "<< num << std::endl;
	}
);
function();
```



### [&var]

表示引用传递捕捉变量var

```C++
int num = 100;
auto function = ([&num]{
		num = 1000;
		std::cout << "num: " << num << std::endl;
	}
);

function();
```

  

### [&]

表示引用传递方式捕捉所有父作用域的变量（包括this）

```C++
int index = 1;
int num = 100;
auto function = ([&]{
		num = 1000;
		index = 2;
		std::cout << "index: "<< index << ", " 
            << "num: "<< num << std::endl;
	}
);

function();
```



### [this]

表示值传递方式捕捉当前的this指针

```C++
#include <iostream>
using namespace std;

class Lambda
{
public:
    void sayHello() {
        std::cout << "Hello" << std::endl;
    };

     void lambda() {
         auto function = [this]{ 
             this->sayHello(); 
         };

         function();
     }
};

int main()
{
    Lambda demo;
    demo.lambda();
}
```

###    [=, &] 

拷贝与引用混合
其中[=,&a,&b]表示以引用传递的方式捕捉变量a和b，以值传递方式捕捉其它所有变量。

```c++
int index = 1;
int num = 100;
auto function = ([=, &index, &num]{
		num = 1000;
		index = 2;
		std::cout << "index: "<< index << ", " 
            << "num: "<< num << std::endl;
	}
);

function();
```

  

[&,a,this]

表示以值传递的方式捕捉变量a和this，引用传递方式捕捉其它所有变量。

不过值得注意的是，捕捉列表不允许变量重复传递。下面一些例子就是典型的重复，会导致编译时期的错误。例如：

[=,a]这里已经以值传递方式捕捉了所有变量，但是重复捕捉a了，会报错的;

[&,&this]这里&已经以引用传递方式捕捉了所有变量，再捕捉this也是一种重复。

如果lambda主体total通过引用访问外部变量，并factor通过值访问外部变量，则以下捕获子句是等效的：

```C++
[&total, factor]
[factor, &total]
[&, factor]
[factor, &]
[=, &total]
[&total, =]
```



### Lambda参数列表

 除了捕获列表之外，lambda还可以接受输入参数。参数列表是可选的，并且在大多数方面类似于函数的参数列表。

```C++
auto function = [] (int first, int second){
    return first + second;
};
	
function(100, 200);
```



### 可变规格mutable

 mutable修饰符， 默认情况下Lambda函数总是一个const函数，mutable可以取消其常量性。在使用该修饰符时，参数列表不可省略（即使参数为空）。

```C++
#include <iostream>
using namespace std;

int main()
{
   int m = 0;
   int n = 0;
   [&, n] (int a) mutable { m = ++n + a; }(4);
   cout << m << endl << n << endl;
}
```



## 异常说明

 你可以使用 throw() 异常规范来指示 lambda 表达式不会引发任何异常。与普通函数一样，如果 lambda 表达式声明 C4297 异常规范且 lambda 体引发异常，Visual C++ 编译器将生成警告 throw() 。

```C++
int main() // C4297 expected 
{ 
 	[]() throw() { throw 5; }(); 
}
```

在MSDN的异常规范 [5] 中，明确指出异常规范是在 C++11 中弃用的 C++ 语言功能。因此这里不建议不建议大家使用。

### 返回类型

 Lambda表达式的返回类型会自动推导。除非你指定了返回类型，否则不必使用关键字。返回型类似于通常的方法或函数的返回型部分。但是，返回类型必须在参数列表之后，并且必须在返回类型->之前包含类型关键字。如果lambda主体仅包含一个return语句或该表达式未返回值，则可以省略Lambda表达式的return-type部分。如果lambda主体包含一个return语句，则编译器将从return表达式的类型中推断出return类型。否则，编译器将返回类型推导为void。

```C++
auto x1 = [](int i){ return i; };
```

2.3.6 Lambda函数体

 Lambda表达式的lambda主体（标准语法中的复合语句）可以包含普通方法或函数的主体可以包含的任何内容。普通函数和lambda表达式的主体都可以访问以下类型的变量：

- 捕获变量
- 形参变量
- 局部声明的变量
- 类数据成员，当在类内声明**`this`**并被捕获时
- 具有静态存储持续时间的任何变量，例如全局变量

    

```C++
#include <iostream>
using namespace std;

int main()
{
   int m = 0;
   int n = 0;
   [&, n] (int a) mutable { m = ++n + a; }(4);
   cout << m << endl << n << endl;
}
```



3.Lambda表达式的优缺点
3.1 Lambda表达式的优点

可以直接在需要调用函数的位置定义短小精悍的函数，而不需要预先定义好函数

```
 std::find_if(v.begin(), v.end(), [](int& item){return item > 2});
```

使用Lamdba表达式变得更加紧凑，结构层次更加明显、代码可读性更好

3.2 Lambda表达式的缺点

Lamdba表达式语法比较灵活，增加了阅读代码的难度
对于函数复用无能为力

4.Lambda表达式工作原理
4.1 Lambda表达式工作原理

 编译器会把一个lambda表达式生成一个匿名类的匿名对象，并在类中重载函数调用运算符,实现了一个operator()方法。

```C++
auto print = []{cout << "Hello World!" << endl; };
```

 编译器会把上面这一句翻译为下面的代码:

```C++
class print_class
{
public:
	void operator()(void) const
	{
		cout << "Hello World！" << endl;
	}
};
```

//用构造的类创建对象，print此时就是一个函数对象

```C++
auto print = print_class();
```

4.2 C++仿函数

 仿函数（functor）又称为函数对象（function object）是一个能行使函数功能的类。仿函数的语法几乎和我们普通的函数调用一样，不过作为仿函数的类，都必须重载operator()运算符，仿函数与Lamdba表达式的作用是一致的。举个例子：

```C++
#include <iostream>
#include <string>
using namespace std;

class Functor
{
public:
    void operator() (const string& str) const
    {
        cout << str << endl;
    }
};

int main()
{
    Functor myFunctor;
    myFunctor("Hello world!");
    return 0;
}
```



5.Lamdba表达式适用场景
5.1 Lamdba表达式应用于STL算法库

```C++
// for_each应用实例
int a[4] = {11, 2, 33, 4};
sort(a, a+4, [=](int x, int y) -> bool { return x%10 < y%10; } );
for_each(a, a+4, [=](int x) { cout << x << " ";} );
```



```C++
// find_if应用实例
int x = 5;
int y = 10;
deque<int> coll = { 1, 3, 19, 5, 13, 7, 11, 2, 17 };
auto pos = find_if(coll.cbegin(), coll.cend(), [=](int i) {                 
    return i > x && i < y;
});
```



```C++
// remove_if应用实例
std::vector<int> vec_data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int x = 5;
vec_data.erase(std::remove_if(vec.date.begin(), vec_data.end(), [](int i) { 
    return n < x;}), vec_data.end());

std::for_each(vec.date.begin(), vec_data.end(), [](int i) { 
    std::cout << i << std::endl;});
```





5.2 短小不需要复用函数场景

```C++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
    int data[6] = { 3, 4, 12, 2, 1, 6 };
    vector<int> testdata;
    testdata.insert(testdata.begin(), data, data + 6);

    // 对于比较大小的逻辑，使用lamdba不需要在重新定义一个函数
    sort(testdata.begin(), testdata.end(), [](int a, int b){ 
        return a > b; });
    
    return 0;

}
```





5.3 Lamdba表达式应用于多线程场景

```C++
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

int main()
{
    // vector 容器存储线程
    std::vector<std::thread> workers;
    for (int i = 0; i < 5; i++) 
    {
        workers.push_back(std::thread([]() 
        {
            std::cout << "thread function\n";
        }));
    }
    std::cout << "main thread\n";

    // 通过 for_each 循环每一个线程
    // 第三个参数赋值一个task任务
    // 符号'[]'会告诉编译器我们正在用一个匿名函数
    // lambda函数将它的参数作为线程的引用t
    // 然后一个一个的join
    std::for_each(workers.begin(), workers.end(), [](std::thread &t;) 
    {
        t.join();
    });
    
    return 0;

}


```



```C++
std::mutex mutex;
std::condition_variable condition;
std::queue<std::string> queue_data;

std::thread threadBody([&]{
	std::unique_lock<std::mutex> lock_log(mutex);
	condition.wait(lock_log, [&]{
		return !queue_data.front();
	});
	std::cout << "queue data: " << queue_data.front();
	lock_log.unlock();
});

queue_data.push("this is my data");
condition.notity_one();

if(threadBody.joinable())
{
	threadBody.join();
}
```

5.4 Lamdba表达式应用于函数指针与function

```C++
#include <iostream>
#include <functional>
using namespace std;

int main(void)
{
    int x = 8, y = 9;
    auto add = [](int a, int b) { return a + b; };
    std::function<int(int, int)> Add = [=](int a, int b) { return a + b; };

    cout << "add: " << add(x, y) << endl;
    cout << "Add: " << Add(x, y) << endl;
    
    return 0;

}
```





5.5 Lamdba表达式作为函数的入参

```C++
using FuncCallback = std::function<void(void)>;

void DataCallback(FuncCallback callback)
{
	std::cout << "Start FuncCallback!" << std::endl;
	callback();
	std::cout << "End FuncCallback!" << std::endl;
}

auto callback_handler = [&](){
	std::cout << "This is callback_handler";
};

DataCallback(callback_handler);
```

5.6 Lamdba表达式在QT中的应用

```c++
QTimer *timer=new QTimer;
timer->start(1000);
QObject::connect(timer,&QTimer::timeout,[&](){
        qDebug() << "Lambda表达式";
});
```



```C++
int a = 10;
QString str1 = "汉字博大精深";
connect(pBtn4, &QPushButton::clicked, [=](bool checked){
	qDebug() << a <<str1;
	qDebug() << checked;
	qDebug() << "Hua Windows Lambda Button";
});
```



