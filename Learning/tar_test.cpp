
#include<iostream>
#include<string>
#include <regex>
#include <vector>
#include <filesystem>



bool command_exec(const std::string& cmd, std::vector<std::string>& result_vec) {
    char line[4096] = {0};
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


//judge if contain str
bool containsAnyOf(const std::string& str, const std::vector<std::string>& substrings) {
    for (const auto& sub : substrings) {
        if (str.find(sub) != std::string::npos) {
            return true;
        }
    }
    return false;
}

//get tar directory
std::vector<std::string > get_tar_dir(const std::string& time_str) {
    std::vector<std::string > Nas_path_list;
    std::filesystem::path  Nas_dir = "/opt/usr/Nas/";
    if (std::filesystem::exists(Nas_dir) && std::filesystem::is_directory(Nas_dir)) {
        for (const auto& entry : std::filesystem::directory_iterator(Nas_dir)) {
            std::string record_dir = entry.path().string();
            if (std::filesystem::is_directory(entry.path()) && record_dir.find(time_str) != std::string::npos) {
                Nas_path_list.push_back(record_dir);
                std::cerr << "目录:" << record_dir << std::endl;
            }
        }
    } else {
        std::cerr << "目录不存在或不是一个目录" << std::endl;
    }
    return Nas_path_list;
}
//get tar fileslist
std::vector<std::string> get_tar_files(const std::string& tar_dirs) {
    std::vector<std::string> tar_files;
    std::vector<std::string> filter_str = {"FM", "MINI", "CANFD", "LOG", "res_collect"};
    if (!tar_dirs.empty()) {
        // for (const auto& tar_dir1 : tar_dirs) {
        std::filesystem::path tar_dir = tar_dirs;
        std::cerr << "get_tar_files:" << tar_dir << std::endl;
        for (const auto& tar_file : std::filesystem::directory_iterator(tar_dir)) {
            if (std::filesystem::is_regular_file(tar_file) && containsAnyOf(tar_file.path().string(), filter_str)) {
                tar_files.push_back(tar_file.path().string());

            }

        }
        // }
    }
    return tar_files;
}


int start_tar_command(const std::string& time_str) {
    int tar_status = 0;
    int tar_empty_status = 0;
    std::vector<std::string > tar_dirs = get_tar_dir( time_str);
    if (!tar_dirs.empty()) {
        for (auto& dir : tar_dirs)
        {
            std::vector<std::string> tar_files = get_tar_files(dir);
            if (tar_files.empty()) {
                // LOGGER()->info("tar_files is empty!");
                // return 0;
                tar_empty_status++;
                std::cerr << "tar_empty_status:" << tar_empty_status;
                continue;
            }
            std::string files_str ;
            for (const auto & file : tar_files) {
                files_str = files_str + " " + file + " ";
            }
            std::string tar_file = dir + ".tar.gz";
            std::string tar_command = " tar cvzf " + tar_file  + files_str;
            std::cerr << tar_command << std::endl;
            // LOGGER()->info("cmd exec : {0}", tar_command);
            std::vector<std::string> result_vec ;
            bool ret = command_exec(tar_command, result_vec);
            if (ret) {
                for (const auto& str : result_vec) {
                    std::cerr << str;
                }
                //
            }
            else {
                // return 0;
            }
            if (std::filesystem::exists(tar_file)) {
                tar_status = 1;
            }
        }
    }
    if (tar_dirs.size() != 0 && tar_empty_status == tar_dirs.size()) {
        tar_status = -1;
    }
    return tar_status;
}



int main() {

    std::string time_str = "20240719";
    int start_status = start_tar_command(time_str);
    if (start_status == 1) {
        std::cerr << "压缩成功！";
    }
    if (start_status == -1) {
        std::cerr << "可压缩文件为空！";
    }
    if (start_status == 0) {
        std::cerr << "压缩失败！";
    }




    return 0;
}