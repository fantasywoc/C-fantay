#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>

class TaskManager {
public:
    TaskManager(size_t maxTasks) : maxTasks_(maxTasks), stop_(false) {}

    ~TaskManager() {
        stop();
    }

    void start(size_t numWorkers) {
        for (size_t i = 0; i < numWorkers; ++i) {
            workers_.emplace_back(&TaskManager::workerThread, this);
        }
    }

    void addTask(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [this] { return tasks_.size() < maxTasks_ || stop_; });
            if (stop_) return;
            tasks_.emplace(std::move(task));
        }
        cv_.notify_one();
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stop_ = true;
        }
        cv_.notify_all();
        for (std::thread &worker : workers_) {
            worker.join();
        }
    }

private:
    void workerThread() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                cv_.wait(lock, [this] { return stop_ || !tasks_.empty(); });
                if (stop_ && tasks_.empty()) return;
                if (!tasks_.empty()) {
                    task = std::move(tasks_.front());
                    tasks_.pop();
                }
            }
            if (task) {
                task(); // 执行任务
            }
        }
    }

    std::queue<std::function<void()>> tasks_;
    std::vector<std::thread> workers_;
    std::mutex mutex_;
    std::condition_variable cv_;
    size_t maxTasks_;
    bool stop_;
};

// 示例任务
void exampleTask(int id) {
    std::cout << "Processing task " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    TaskManager manager(5); // 最大同时任务数为5
    manager.start(3); // 启动3个工作线程

    for (int i = 0; i < 10; ++i) {
        manager.addTask([i] { exampleTask(i); });
    }

    std::this_thread::sleep_for(std::chrono::seconds(10)); // 等待所有任务完成
    manager.stop(); // 停止管理器
    return 0;
}
