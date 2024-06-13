#include<iostream>
#include <cstdio>  
#include <vector>  
#include <string>  
#include <cstring>
#include <iterator> 
#include "command.h"

  
bool command_exec(const std::string& cmd, std::vector<std::string>& result_vec) {  
    char line[MAX_BUFFER_SIZE] = {0};  
    FILE* fp = popen(cmd.c_str(), "r");  
    if (fp == NULL) {  
        return false;  
    }  
      
    while (fgets(line, sizeof(line), fp) != NULL) {  
        // 移除行尾的换行符（如果存在）  
        line[strcspn(line, "\n")] = 0; // 使用 strcspn 替代 find_last_not_of  
        result_vec.push_back(std::string(line));  
    }  
      
    pclose(fp);  
      
    return true;  
}

// 模板函数，用于打印任意类型的std::vector  
template <typename T>  
void printVector(const std::vector<T>& vec) {  
    
    for (const auto& element : vec) {  
        std::cout << element << " ";  
    }  
    std::cout << std::endl;  
}  


int main(){
    std::string cmd = "ls  ";

    std::vector<std::string> result_vec;
    bool ret=command_exec(cmd,result_vec);
    
    printVector(result_vec);
    
    // 或者，如果你想要更简洁的代码，可以使用C++11的范围for循环（上面已经使用了）  
    // 或者使用std::copy和std::ostream_iterator  
   // std::copy(result_vec.begin(), result_vec.end(),   
    //           std::ostream_iterator<std::string>(std::cout, " ")); 
    //std::cout << std::endl; // 同样输出换行符  

    return 0;

}
