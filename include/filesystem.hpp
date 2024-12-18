#pragma once

#include <fstream>
#include <string>

const std::string DATA_DIR = "data/";
const std::string LOG_DIR = "logs/";

void ensure_directory_exists(const std::string &directory);

std::ifstream read_file(std::string_view filename);
std::ofstream create_file(std::string_view filename);
std::ofstream append_file(std::string_view filename);
std::ofstream overwrite_file(std::string_view filename);

bool overwrite_file_line(std::string_view filename, std::string_view line, size_t line_number);