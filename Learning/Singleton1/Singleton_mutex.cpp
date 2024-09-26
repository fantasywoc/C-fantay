// 代码解释

//     Singleton 类:
//         这个类的构造函数是私有的，防止外部直接创建实例。
//         使用 std::unique_ptr 来管理单例的实例，确保只有一个实例存在。
//         std::once_flag 和 std::call_once 用于确保在多线程环境中只初始化一次实例。

//     静态成员变量:
//         _instance 用于存储单例对象的唯一实例。
//         init_flag 用于保证实例的唯一初始化。

//     获取实例方法:
//         get_instance() 方法用于获取单例实例。通过 std::call_once 确保初始化过程的线程安全。

//     删除拷贝构造函数和赋值操作符:
//         通过将拷贝构造函数和赋值操作符设置为 delete，确保不可以复制单例对象。

// 完善代码和调用示例

// 以下是完善后的代码，包括 main 函数的调用示例：

// 代码说明

//     示例方法 do_something: 这个方法只是打印一条消息，演示如何使用单例实例。
//     main 函数:
//         获取单例实例并调用 do_something() 方法，展示了如何使用这个单例类。

// 编译与运行

// 可以使用以下命令编译并运行该代码：

// bash

// g++ -std=c++11 -o singleton_example singleton_example.cpp
// ./singleton_example

// 你应该会看到输出：

// Doing something in the Singleton instance.

// 这表明单例模式工作正常，实例成功调用了方法。


// 单例模式的定义：保证一个类仅有一个实例，并提供一个该实例的全局访问点。
// 线程锁实现


#include <iostream>
#include <mutex>
#include <memory>

class Singleton {
public:
    static Singleton* get_instance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!_instance) {
            _instance.reset(new Singleton());
        }
        return _instance.get();
    }

    void do_something() {
        std::cout << "Doing something in the Singleton instance." << std::endl;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {}

    static std::unique_ptr<Singleton> _instance;
    static std::mutex mutex_;
};

// 静态成员变量初始化
std::unique_ptr<Singleton> Singleton::_instance;
std::mutex Singleton::mutex_;

int main() {
    Singleton* instance = Singleton::get_instance();
    instance->do_something();
    return 0;
}
