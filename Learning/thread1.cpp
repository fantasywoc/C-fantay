#include <iostream>
#include <thread>

void task1() {
    std::cout << "Task 1" << std::endl;
}

void task2() {
    std::cout << "Task 2" << std::endl;
}

int main() {
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join(); // 等待线程 t1 完成
    t2.join(); // 等待线程 t2 完成

    return 0;
}