#include "Singleton_call_once.cpp"


void threadFunction(int th) {
    Singleton::getInstance()->doSomething(th);
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