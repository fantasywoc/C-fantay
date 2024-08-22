#include <iostream>



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

int main() {
    test_static();
    myFunction(); // 输出: 这是第一次调用函数！

    myFunction(); // 输出: 这不是第一次调用函数。

    myFunction(); // 输出: 这不是第一次调用函数。



    return 0;

}