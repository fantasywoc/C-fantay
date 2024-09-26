
#  Singleton call_once neet link pthread 
g++  Singleton_call_once.cpp  -std=c++11 -o Singleton_call_once  -lpthread
```c++
//g++ 
#include <iostream>
#include <mutex>
#include <memory>
#include <thread>
class Singleton {
private:
    static std::unique_ptr<Singleton> instance_;
    static std::once_flag flag_;

    Singleton() {
        std::cout << "Singleton created" << std::endl;
    }

public:
    static Singleton* getInstance() {
        std::call_once(flag_, [] {
            instance_.reset(new Singleton());
        });
        return instance_.get();
    }

    void doSomething(int th) {
        std::cout << "Doing something..." << th<< std::endl;
    }
};

std::unique_ptr<Singleton> Singleton::instance_ = nullptr;
std::once_flag Singleton::flag_;

void threadFunction(int th) {
    Singleton* instance = Singleton::getInstance();
    instance->doSomething(th);
}

int main() {
    std::thread t1(threadFunction,1);
    t1.join();
    std::cout<< "Singleton" <<std::endl;
    std::thread t2(threadFunction,2);
    t2.join();
    std::cout<< "Singleton t2 over" <<std::endl;

    return 0;
}
```


