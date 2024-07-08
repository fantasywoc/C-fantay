
#include <sqlite3.h>
#include <iostream>
#include <string>

// SQLite 数据库文件名
const char* DB_FILE = "todo_list.db";

// 回调函数，用于处理查询结果
static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    std::cout << "--- Todo List ---" << std::endl;
    for (i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << "-----------------" << std::endl;
    return 0;
}

int main() {
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    // 打开数据库连接
    rc = sqlite3_open(DB_FILE, &db);
    if (rc) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // 创建待办事项表
    const char* sql_create_table =
        "CREATE TABLE IF NOT EXISTS todo ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "task TEXT NOT NULL);";
    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    // 添加待办事项
    std::string task;
    std::cout << "Enter a task to add (or 'q' to quit): ";
    while (std::getline(std::cin, task)) {
        if (task == "q") {
            break;
        }
        std::string sql_insert = "INSERT INTO todo (task) VALUES ('" + task + "');";
        rc = sqlite3_exec(db, sql_insert.c_str(), callback, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        }
        std::cout << "Task added successfully. Enter another task (or 'q' to quit): ";
    }

    // 显示所有待办事项
    const char* sql_select = "SELECT * FROM todo;";
    rc = sqlite3_exec(db, sql_select, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    // 关闭数据库连接
    sqlite3_close(db);

    return 0;
}
