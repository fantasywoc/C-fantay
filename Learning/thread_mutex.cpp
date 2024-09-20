// g++ thread_mutex.cpp -std=c++11 -o thread_mutex -lpthread

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool deadlock_detected = false;

// 共享锁（读锁）操作
void shared_lock_read(const std::string& file_path) {
    int fd = open(file_path.c_str(), O_RDONLY);
    if (fd < 0) {
        std::cerr << "Failed to open file for reading.\n";
        return;
    }

    // 获取共享锁
    if (flock(fd, LOCK_SH) != 0) {
        std::cerr << "Failed to acquire shared lock.\n";
        close(fd);
        return;
    }

    std::cout << "Reading file contents:\n";
    std::ifstream file(file_path);
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    // 释放共享锁
    flock(fd, LOCK_UN);
    close(fd);
}

// 排他锁（写锁）操作
void exclusive_lock_write(const std::string& file_path, const std::string& content, int delay) {
    int fd = open(file_path.c_str(), O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        std::cerr << "Failed to open file for writing.\n";
        return;
    }

    // 获取排他锁
    if (flock(fd, LOCK_EX) != 0) {
        std::cerr << "Failed to acquire exclusive lock.\n";
        close(fd);
        return;
    }

    std::cout << "Writing to file: " << content << std::endl;
    lseek(fd, 0, SEEK_END); // Move to the end of file
    write(fd, (content + "\n").c_str(), content.size() + 1);
    
    // 模拟长时间的操作
    // std::this_thread::sleep_for(std::chrono::seconds(delay));

    // 释放排他锁
    flock(fd, LOCK_UN);
    close(fd);
}

// 死锁模拟和检测
void deadlock_simulation(const std::string& file_path) {
    std::unique_lock<std::mutex> lock(mtx);
    deadlock_detected = true;
    cv.wait(lock, [] { return !deadlock_detected; }); // 模拟死锁检测
    std::cout << "Deadlock detected and resolved.\n";
}

int main() {
    std::string file_path = "example.txt";

    // 创建并启动线程
    std::thread writer1(exclusive_lock_write, file_path, "Line 1", 5);
    std::thread writer2(exclusive_lock_write, file_path, "Line 2", 5);
    std::thread reader(shared_lock_read, file_path);
    // std::thread deadlock_thread(deadlock_simulation, file_path);

    writer1.join();
    writer2.join();
    reader.join();
    // deadlock_thread.join();

    return 0;
}
