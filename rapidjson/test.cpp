#include<iostream>
#include<string>
#include <regex>
// #include <fstream>

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>


#include "rapidjson/document.h"

#include "rapidjson/writer.h"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/error/en.h"


const int MAX_BUFFER_SIZE = 4096;

bool command_exec(const std::string& cmd, std::vector<std::string>& result_vec) {
	char line[MAX_BUFFER_SIZE] = {0};
	FILE* fp = nullptr;
	if ((fp = popen(cmd.c_str(), "r")) == NULL) { return false; }

	while (fgets(line, sizeof(line) - 1, fp) != NULL) {
		result_vec.push_back(std::string(line));
	}
	pclose(fp);
	return true;
}

// 将字符串表示的日期时间转换为std::chrono::system_clock::time_point

std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateTime) {
	std::istringstream ss(dateTime);
	std::tm tm = {};
	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
	if (ss.fail()) {
		throw std::runtime_error("Failed to parse date time string");
	}
	return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}


// 将时间点转换为可读的日期时间字符串
std::string timePointToString(const std::chrono::system_clock::time_point& tp) {
	std::time_t tt = std::chrono::system_clock::to_time_t(tp);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S");
	return ss.str();

}

void FormatJson(const rapidjson::Value & value, std::stringstream & ss, int indent = 0) {
	std::string indentStr(indent, ' ');
	switch (value.GetType()) {
	case rapidjson::kObjectType: {
		ss << "{\n";
		for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it) {
			ss << indentStr << "\"" << it->name.GetString() << "\": ";
			FormatJson(it->value, ss, indent + 4);
			if (it != value.MemberEnd() - 1) {
				ss << ",\n";
			} else {
				ss << "\n";
			}
		}
		ss << indentStr << "}";
		break;
	}
	case rapidjson::kArrayType: {
		ss << "[\n";
		for (rapidjson::SizeType i = 0; i < value.Size(); ++i) {
			ss << indentStr << "  ";
			FormatJson(value[i], ss, indent + 4);
			if (i != value.Size() - 1) {
				ss << ",\n";
			} else {
				ss << "\n";
			}
		}
		ss << indentStr << "]";
		break;
	}
	case rapidjson::kStringType:
		ss << "\"" << value.GetString() << "\"";
		break;
	case rapidjson::kNumberType:
		if (value.IsInt()) {
			ss << value.GetInt();
		} else if (value.IsUint()) {
			ss << value.GetUint();
		} else if (value.IsDouble()) {
			ss << value.GetDouble();
		}
		break;
	case rapidjson::kTrueType:
		ss << "true";
		break;
	case rapidjson::kFalseType:
		ss << "false";
		break;
	case rapidjson::kNullType:
		ss << "null";
		break;
	default:
		// 处理未知类型或错误
		ss << "UNKNOWN";
	}
}


std::vector<std::string>  calculate_the_start_and_end_time(const std::string& nowtime_str ) {
	std::vector<std::string> result_time;
	auto tp = stringToTimePoint(nowtime_str);
	// 20秒
	auto duration = std::chrono::seconds(20);
	auto start_time = tp - duration;
	auto end_time = tp + duration;
	// swich to sting
	std::string newDateTimeStr_start = timePointToString(start_time);
	result_time.push_back(newDateTimeStr_start);
	std::string newDateTimeStr_end = timePointToString(end_time);
	result_time.push_back(newDateTimeStr_end);
	std::cout << "newDateTimeStr_end: " << newDateTimeStr_start << " newDateTimeStr_end:" << newDateTimeStr_end << std::endl;

	return result_time;
}

int main() {

	char intact_command1[2048] = {0};

	std::string cat = "/opt/usr/col/planning/stat/json";
	snprintf(intact_command1, sizeof(intact_command1), "%s \"  cat  %s \" ", " FLAGS_orin_time_command.c_str()", cat.c_str());
//     sprintf(intact_command, "%s \"  cat  %s \" ", "FLAGS_orin_time_command.c_str()",cat.c_str());
	std::string date_command =  std::string(intact_command1);
	std::cout << "------" << date_command << std::endl;

	std::string date = "date  \"+%Y-%m-%d %H:%M:%S\" ";
	std::cout << date << std::endl;

	std::string command = date;
	std::vector<std::string> result_vec;
	bool ret_date = command_exec(command, result_vec);
	for (const auto& str : result_vec) {
		std::cout << str << " ";
	}

	std::vector<std::string> teme = calculate_the_start_and_end_time("2024-07-02 10:21:20");
	for (const auto& str1 : teme) {
		std::cout << "----------" << str1 << "------------";
	}


	std::string start_time = "2024-07-02 10:21:00";
	std::string end_time = "2024-07-02 10:22:00" ;
	// bash -c ' sudo -u neousys ssh orin  " find ./stat/ -type f -newermt \"2024-04-17 06:17:20\" ! -newermt \"2024-04-17 06:17:46\" | sort -nr | head -n 1 | cut -d\" \" -f2- " '
//bash -c 'ssh orin "find ~/stat/ -type f -newermt \"2024-04-17 06:17:20\" ! -newermt \"2024-04-17 06:17:46\" | sort -nr | head -n 1 | cut -d\" \" -f2-"'
// bash -c 'ssh orin "find ~/stat/ -type f -newermt \"2024-04-17 06:17:20\" ! -newermt \"2024-04-17 06:17:46\" | sort -nr | head -n 1 | cut -d\" \" -f2-"'

	std::string shell_cmd = "  find ./stat/ -type f -newermt \"" + start_time + "\" ! -newermt \"" + end_time + "\" | sort -nr | head -n 1 | cut -d\" \" -f2-   " ;
	std::string shell_cmd1 = " sudo -u neousys ssh orin \" find /opt/usr/col/planning/stat/  -type f -newermt \\\"" + start_time + " \\\" ! -newermt \\\"" + end_time + "\\\" | sort -nr | head -n 1 | cut -d\\\" \\\" -f2- \"  " ;
	std::cout << shell_cmd << std::endl;
	std::cout << "---" << shell_cmd1 << std::endl;
	// std::string find_new_json = "find . / stat / -type f \\( -newermt \"2024-07-02 10:21:00\" ! -newermt \"2024-07-02 10:21:59\" \\) -print | sort -nr | head -n 1 | cut -d' ' -f2- " ;
	std::vector<std::string> result_vec_find;
	bool ret_find = command_exec(shell_cmd, result_vec_find);
	for (const auto& str : result_vec_find) {
		std::cout << str << std::endl;
	}

	std::string shell_cmd_find = " find /opt/usr/col/planning/stat/  -type f -newermt \\\"" + start_time + " \\\" ! -newermt \\\"" + start_time + "\\\" | sort -nr | head -n 1 | cut -d\\\" \\\" -f2-   " ;

	char intact_command_find[2048] = {0};
	sprintf(intact_command_find, " %s   \"  %s \" ", "FLAGS_orin_sshpass_prefix.c_str()", shell_cmd_find.c_str());
	std::string find_command =  std::string(intact_command_find);
	std::cout << find_command << std::endl;




	std::string cat_cmd = " cat " + result_vec_find[0];
	std::vector<std::string> result_vec_cat;
	bool ret_cat = command_exec(cat_cmd, result_vec_cat);
	std::cout << "result_vec_cat[0]" << " : --------------------------------------" << std::endl;
	// std::cout << result_vec_cat[0] << std::endl;

	const char* jsonStr = result_vec_cat[0].c_str();
	// 创建Document对象
	rapidjson::Document document;
	rapidjson::ParseResult ok = document.Parse(jsonStr);

	if (!ok) {
		//  GetParseError_En 获取异常
		std::cerr << "Parse error: " << rapidjson::GetParseError_En(document.GetParseError()) << std::endl;
	}
	else {
		std::cout << "parse success" << "  ";
	}
	//格式化输出
	std::stringstream ss;
	FormatJson(document, ss);
	std::cout << ss.str() << std::endl;
	std::vector<std::string> result_json;
	if (document.IsArray() && document.Size() > 0) {
		const auto& driving_mode = document[0]["driving_mode"];
		if (driving_mode == 3) {
			std::cout << "driving_mode == 3" << std::endl;
			const auto & obj = document[0]["data"];
			if (obj.HasMember("avp_parking_time")) {
				double avp_parking_time = obj["avp_parking_time"].GetDouble();

				result_json.push_back(std::to_string(avp_parking_time));
				std::cout << "avp_parking_time: " << avp_parking_time << std::endl;
			}
			else {
				result_json.push_back("");
				std::cout << "steer_angle: " << "" << std::endl;
			}
			if (obj.HasMember("avp_parking_shift_counter")) {
				double avp_parking_shift_counter = obj["avp_parking_shift_counter"].GetDouble();
				result_json.push_back(std::to_string(avp_parking_shift_counter));
				std::cout << "avp_parking_shift_counter: " << avp_parking_shift_counter << std::endl;
			}
			else {
				result_json.push_back("");
				std::cout << "steer_angle: " << "" << std::endl;
			}
			if (obj.HasMember("steer_angle")) {
				double steer_angle = obj["steer_angle"].GetDouble();
				result_json.push_back(std::to_string(steer_angle));
				std::cout << "steer_angle: " << steer_angle << std::endl;
			}
			else {
				result_json.push_back("");
				std::cout << "steer_angle: " << "" << std::endl;
			}
		}
	}

	for (const auto& str1 : result_json) {
		std::cout << str1 << std::endl;
	}



	//std::string shell_cmd1 = "  ssh orin \" find ./stat/ -type f -newermt \\\"" + "start_time" + " \\\" ! -newermt \\\"" + "end_time" + "\\\" | sort -nr | head -n 1 | cut -d\\\" \\\" -f2- \"  " ;
//     std::string shell_cmd1 = "  ssh orin \" find ./stat/ -type f -newermt \\\"" + std::string("start_time") + "\\\" ! -newermt \\\"" + std::string("end_time") + "\\\" | sort -nr | head -n 1 | cut -d\\\" \\\" -f2- \"  " ;

//     char intact_command1[2048] = {0};
//     sprintf(intact_command1," bash -c  \" %s \"  " , shell_cmd1.c_str());
//     std:string date_command1=std::string(intact_command1);
//     std::cout<<date_command1<<";";
//       std::string shell_cmd_find= " bash -c \' sudo -u neousys ssh orin  \" find ./stat/ -type f -newermt \\\"" +  "start_end_time[0]"  + " \\\" ! -newermt \\\"" + "start_end_time[1]" + "\\\" | sort -nr | head -n 1 | cut -d\\\" \\\" -f2- \" \' " ;
	// std::string shell_cmd_find = " bash -c \" ssh orin \" find ./stat/ -type f -newermt \\\"" + start_time + " \\\" ! -newermt \\\"" + end_time + "\\\" | sort -nr | head -n 1 | cut -d\\\" \\\" -f2- \" \" " ;

	// std::cout << shell_cmd_find << ";";
	return 0;


	bool file_exists(const std::string & name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

}

