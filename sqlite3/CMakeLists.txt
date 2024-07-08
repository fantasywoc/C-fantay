cmake_minimum_required(VERSION 3.0)

project(Sqlite3Example)

# 假设你有一个SQLite3的自定义安装路径
set(SQLITE3_DIR ${CMAKE_SOURCE_DIR})

# 设置CMAKE_PREFIX_PATH以包含SQLite3的安装路径
list(APPEND CMAKE_PREFIX_PATH ${SQLITE3_DIR})

# 使用FindSQLite3模块（如果存在的话，否则你可能需要自己写一个）
find_package(SQLite3 REQUIRED)

if(SQLITE3_FOUND)
    message("sqlite3 found: ${SQLITE3_INCLUDE_DIRS} ${SQLITE3_LIBRARIES}")
    include_directories("/home/f/data/sqlite3/include")
    add_executable(Sqlite3Example ${CMAKE_SOURCE_DIR}/src/main.cpp)
    target_include_directories(Sqlite3Example PRIVATE ${SQLITE3_INCLUDE_DIRS})
    target_link_libraries(Sqlite3Example SQLite::SQLite3)

else()
    message(FATAL_ERROR "sqlite3 not found")
endif()

