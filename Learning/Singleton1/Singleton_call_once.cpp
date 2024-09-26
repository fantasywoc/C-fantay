// #include <iostream>
// #include <mutex>
// #include <memory>

// class Singleton {
// public:
//     static Singleton* get_instance() {
//         std::call_once(init_instance_flag, []() {
//             _instance.reset(new Singleton());
//         });
//         return _instance.get();
//     }

//     void do_something() {
//         std::cout << "Doing something in the Singleton instance." << std::endl;
//     }

//     // Delete copy constructor and assignment operator
//     Singleton(const Singleton&) = delete;
//     Singleton& operator=(const Singleton&) = delete;

// private:
//     Singleton() {}

//     static std::unique_ptr<Singleton> _instance;
//     static std::once_flag init_instance_flag;
// };

// // Initialize static members
// std::unique_ptr<Singleton> Singleton::_instance;
// std::once_flag Singleton::init_instance_flag;

// int main() {
//     Singleton* instance = Singleton::get_instance();
//     instance->do_something();
//     return 0;
// }

//需要使用多线程模块，并且链接到pthread库，运行才不会报 std::system_error

#include"Singleton_call_once.hpp"
#include <iostream>
#include <mutex>
#include <memory>
#include <thread>



std::unique_ptr<Singleton> Singleton::instance_ = nullptr;
std::once_flag Singleton::flag_;

Singleton::Singleton() {
    std::cout << "Singleton created" << std::endl;
}


Singleton* Singleton::getInstance() {
    std::call_once(flag_, [] {
        instance_.reset(new Singleton());
    });
    return instance_.get();
}

void Singleton::doSomething(int th) {
    std::cout << "Doing something..." << th<< std::endl;
}






