#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <optional>
#include <unordered_map>
#include <vector>
#include <cassert>

#define UTF8TOK_IMPLEMENTATION
#include "../utf8tok.h"

namespace utf8tok
{
namespace generator
{
    std::string_view remove_comments(std::string_view line);

    std::optional<std::pair<std::string_view, std::string_view>> split(std::string_view view,
                                                                       std::string_view separator);

    std::string_view trim(std::string_view view);

    std::pair<code_point, code_point> parse_range(std::string_view range);

    int read_properties(std::ifstream stream,
                        std::vector<std::pair<code_point_range, code_point>> &grapheme_break_range_with_length);

    int generate_header_file(int argc, char **argv);
}
}

int main(int argc, char* argv[])
{
    return utf8tok::generator::generate_header_file(argc, argv);
}
