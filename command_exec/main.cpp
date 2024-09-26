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


void fun9(int a){
    std::cout<< "int:"<<__PRETTY_FUNCTION__<<std::endl;
}

// 空指针
void fun9(int* a){
    std::cout<<__PRETTY_FUNCTION__<<std::endl;
}

#include <iostream>

void exampleFunction() {
    std::cout << "Function Name: " << __FUNCTION__ << std::endl;
    std::cout << "File Name: " << __FILE__ << std::endl;
    std::cout << "Line Number: " << __LINE__ << std::endl;
    std::cout << "Compiled on: " << __DATE__ << " at " << __TIME__ << std::endl;
    std::cout << "Compiled time: " << __DATE__ << " at " << __TIME__ << std::endl;
    std::cout << "Compiler version: " << __VERSION__ << std::endl;
    std::cout << "Character bit size: " << __CHAR_BIT__ << std::endl;

#if defined(__cplusplus)
    std::cout << "C++ Standard: " << __cplusplus << std::endl;
#endif

#ifdef _WIN32
    std::cout << "Operating System: Windows" << std::endl;
#elif defined(__linux__)
    std::cout << "Operating System: Linux" << std::endl;
#elif defined(__APPLE__) && defined(__MACH__)
    std::cout << "Operating System: macOS" << std::endl;
#else
    std::cout << "Operating System: Unknown" << std::endl;
#endif



#if defined(__STDC__)
    std::cout << "This compiler conforms to ANSI C." << std::endl;
#else
    std::cout << "This compiler does not conform to ANSI C." << std::endl;
#endif

#ifdef __GNUC__
    std::cout << "GCC Version: " << __GNUC__ << "." 
              << __GNUC_MINOR__ << "." 
              << __GNUC_PATCHLEVEL__ << std::endl;
#else
    std::cout << "This is not a GCC compiler." << std::endl;
#endif

#if __cplusplus >= 201103L
    std::cout << "C++ standard: C++11 or later." << std::endl;
#elif __cplusplus >= 199711L
    std::cout << "C++ standard: C++98." << std::endl;
#else
    std::cout << "C++ standard: pre-standard C++." << std::endl;
#endif

#if defined(__EXCEPTIONS)
    std::cout << "Exceptions are enabled." << std::endl;
#else
    std::cout << "Exceptions are disabled." << std::endl;
#endif


}


int main(){
    std::string cmd = "timeout 2 ping 192.168.3.8";

    std::vector<std::string> result_vec;
    bool ret=command_exec(cmd,result_vec);
    
    printVector(result_vec);
    
    // 或者，如果你想要更简洁的代码，可以使用C++11的范围for循环（上面已经使用了）  
    // 或者使用std::copy和std::ostream_iterator  
   // std::copy(result_vec.begin(), result_vec.end(),   
    //           std::ostream_iterator<std::string>(std::cout, " ")); 
    //std::cout << std::endl; // 同样输出换行符  

    fun9(nullptr);


    exampleFunction();



    return 0;

}
