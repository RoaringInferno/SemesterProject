#include "filesystem.hpp"

#include <filesystem>

void ensure_directory_exists(const std::string &directory)
{
    std::filesystem::create_directory(directory);
}