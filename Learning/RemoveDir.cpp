//build   g++ -std=c++17 -Wall RemoveDir.cpp -o ./Remove
//support delete file and 
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
int remove_dir(const char *dir) {
    char cur_dir[] = ".";
    char up_dir[] = "..";
    char dir_name[512];  // 增加缓冲区大小
    DIR *dirp;
    struct dirent *dp;
    struct stat dir_stat;
    // 检查目录是否存在
    if (0 != access(dir, F_OK)) {
        return 0;
    }
    // 获取目录属性
    if (0 > stat(dir, &dir_stat)) {
        perror("get directory stat error");
        return -1;
    }
    if (S_ISREG(dir_stat.st_mode)) {  // 普通文件直接删除
        if (remove(dir) != 0) {
            perror("remove error");
            return -1;
        }
    } else if (S_ISDIR(dir_stat.st_mode)) {  // 目录文件，递归删除目录中内容
        dirp = opendir(dir);
        if (dirp == NULL) {
            perror("opendir error");
            return -1;
        }
        while ((dp = readdir(dirp)) != NULL) {
            // 忽略 . 和 ..
            if ((0 == strcmp(cur_dir, dp->d_name)) || (0 == strcmp(up_dir, dp->d_name))) {
                continue;
            }

            snprintf(dir_name, sizeof(dir_name), "%s/%s", dir, dp->d_name);
            if (remove_dir(dir_name) != 0) {
            	std::cout<<"remove:"<<dir_name<<std::endl;
                closedir(dirp);
                return -1;
            }
        }
        closedir(dirp);

        if (rmdir(dir) != 0) {  // 删除空目录
            perror("rmdir error");
            return -1;
        }
    } else {
        perror("unknown file type");
        return -1;
    }
    return 0;
}
int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i)
    {
        if(i!=0){
            std::cout << "Remove file " << i << "-->" << argv[i] << std::endl;
        	int res=remove_dir(argv[i]);
        	if(res==0){
                std::cout<<"remove "<< argv[i] <<" success!"<<std::endl;
        	}
        }
    }
    return 0;
}
