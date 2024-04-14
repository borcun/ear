#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

int main() {
    try {
	std::shared_ptr<spdlog::logger> logger = spdlog::basic_logger_mt("basic_logger", "basic-log.txt");
	spdlog::get("basic_logger")->error("test for error");
    }
    catch(const spdlog::spdlog_ex &ex) {
	std::cerr << ex.what() << std::endl;
    }
    
    return 0;
}
