#pragma once

#include <iostream>
#include <mutex>
#include <memory>
#include <thread>

class Singleton {
private:
    static std::unique_ptr<Singleton> instance_;
    static std::once_flag flag_;

    Singleton() ;
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other)=delete;
public:
    static Singleton* getInstance() ;

    void doSomething(int th);
};


