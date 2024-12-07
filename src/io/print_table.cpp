#include "io.hpp"

#include <iostream>

enum JUSTIFICATION : unsigned char
{
    LEFT,
    RIGHT,
    CENTER
};

std::string justify(const std::string &text, size_t width, JUSTIFICATION justification)
{
    if (text.size() == width) {
        return text;
    }
    if (text.size() > width) {
        return text.substr(0, width);
    }
    size_t padding = width - text.size();
    switch (justification) {
        case LEFT:
            return text + std::string(padding, ' ');
        case RIGHT:
            return std::string(padding, ' ') + text;
        case CENTER:
            size_t left_padding = padding / 2;
            size_t right_padding = padding - left_padding;
            return std::string(left_padding, ' ') + text + std::string(right_padding, ' ');
    }
}

void print_table(const std::vector<std::string> &header, const std::vector<std::vector<std::string>> &table)
{
    size_t column_count = header.size();
    size_t row_count = table.size();
    std::vector<size_t> column_widths(column_count, 0);
    for (size_t i = 0; i < column_count; i++) {
        std::vector<size_t> cell_widths(row_count+1, 0);
        cell_widths[0] = header[i].size();
        for (size_t j = 0; j < row_count; j++) {
            cell_widths[j+1] = table[j][i].size();
        }
        column_widths[i] = *std::max_element(cell_widths.begin(), cell_widths.end());
    }

    auto print_row = [&](const std::vector<std::string> &row) {
        for (size_t i = 0; i < column_count; i++) {
            std::cout << justify(row[i], column_widths[i], JUSTIFICATION::LEFT);
            if (i < column_count - 1) {
                std::cout << " | ";
            }
        }
        std::cout << '\n';
    };
    std::string horizontal_separator;
    {
        size_t total_width = 0;
        for (size_t i = 0; i < column_count; i++) {
            total_width += column_widths[i];
        }
        total_width += column_count - 1; // Account for the column separators
        horizontal_separator = std::string(total_width, '-');
    }

    print_row(header);
    std::cout << horizontal_separator << '\n';
    for (size_t i = 0; i < row_count; i++) {
        print_row(table[i]);
    }
    std::cout << std::flush;
}