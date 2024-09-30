// #include <queue>
// #include <mutex>
// #include <memory>
// #include <iostream>

// // 模拟一个数据库连接类
// class Connection {
// public:
//     Connection() { std::cout << "Connection created" << std::endl; }
//     ~Connection() { std::cout << "Connection destroyed" << std::endl; }
// };

// // 连接池类
// class ConnectionPool {
// public:
//     ConnectionPool(size_t poolSize) {
//         for (size_t i = 0; i < poolSize; ++i) {
//             pool_.push(std::make_shared<Connection>());
//         }
//     }

//     std::shared_ptr<Connection> getConnection() {
//         std::lock_guard<std::mutex> guard(mutex_);
//         if (pool_.empty()) {
//             throw std::runtime_error("No available connections");
//         }
//         auto conn = pool_.front();
//         pool_.pop();
//         return conn;
//     }

//     void releaseConnection(std::shared_ptr<Connection> conn) {
//         std::lock_guard<std::mutex> guard(mutex_);
//         pool_.push(conn);
//     }

// private:
//     std::queue<std::shared_ptr<Connection>> pool_;
//     std::mutex mutex_;
// };

// int main() {
//     ConnectionPool pool(5);

//     auto conn1 = pool.getConnection();
//     auto conn2 = pool.getConnection();

//     pool.releaseConnection(conn1);
//     pool.releaseConnection(conn2);

//     return 0;
// }


#include <queue>
#include <mutex>
#include <memory>
#include <iostream>
#include <string>

// 模拟一个数据库连接类
class Connection {
public:
    Connection(const std::string& name) : name_(name) {
        std::cout << "Connection created: " << name_ << std::endl;
    }
    ~Connection() {
        std::cout << "Connection destroyed: " << name_ << std::endl;
    }

private:
    std::string name_;
};

// 连接池类
class ConnectionPool {
public:
    ConnectionPool(size_t poolSize) {
        for (size_t i = 0; i < poolSize; ++i) {
            pool_.push(std::make_shared<Connection>("Connection_" + std::to_string(i)));
            // std::cout<<"pool_.push:"<<"Connection_"+std::to_string(i)<<std::endl;
        }
    }

    std::shared_ptr<Connection> getConnection() {
        std::lock_guard<std::mutex> guard(mutex_);
        if (pool_.empty()) {
            throw std::runtime_error("No available connections");
        }
        auto conn = pool_.front();
        pool_.pop();
        std::cout <<  "  got a connection->queue:" << pool_.size() <<std::endl;
        return conn;
    }

    void releaseConnection(std::shared_ptr<Connection> conn) {
        std::lock_guard<std::mutex> guard(mutex_);
        pool_.push(conn);
        std::cout <<  "  released a connection->queue:"<<pool_.size() << std::endl;
    }

private:
    std::queue<std::shared_ptr<Connection>> pool_;
    std::mutex mutex_;
};

int main() {
    ConnectionPool pool(5);

    auto conn1 = pool.getConnection();
    auto conn2 = pool.getConnection();

    pool.releaseConnection(conn1);
    pool.releaseConnection(conn2);

    return 0;
}
