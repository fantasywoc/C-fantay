
// 编译方法  g++ thread.cpp -std=c++11 -o thread -lpthread

#include <iostream>
#include <thread>

int sum = 0;

void add(int a, int b) {
    sum += a + b;
}

int main() {
    int a = 5;
    int b = 10;

    std::thread t1(add, a, b);
    std::thread t2(add, a, b);

    // t1.join();
    t2.join();

    std::cout << "Sum: " << sum << std::endl; // 输出结果：Sum: 30
}