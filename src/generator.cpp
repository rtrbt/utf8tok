#include "generator.h"

namespace utf8tok
{
namespace generator
{
std::string grapheme_break_property_strings[utf8tok::grapheme_break_property::Other + 1] =
        {
                "grapheme_break_property::CR",
                "grapheme_break_property::LF",
                "grapheme_break_property::Control",
                "grapheme_break_property::Extend",
                "grapheme_break_property::ZWJ",
                "grapheme_break_property::RI",
                "grapheme_break_property::Prepend",
                "grapheme_break_property::SpacingMark",
                "grapheme_break_property::L",
                "grapheme_break_property::V",
                "grapheme_break_property::T",
                "grapheme_break_property::LV",
                "grapheme_break_property::LVT",
                "grapheme_break_property::Extended_Pictographic",
                "grapheme_break_property::Start_of_text",
                "grapheme_break_property::End_of_text",
                "grapheme_break_property::Other"
        };

std::unordered_map<std::string, utf8tok::grapheme_break_property> grapheme_prop_names =
        {
                {"CR", utf8tok::grapheme_break_property::CR},
                {"LF", utf8tok::grapheme_break_property::LF},
                {"Control", utf8tok::grapheme_break_property::Control},
                {"Extend", utf8tok::grapheme_break_property::Extend},
                {"ZWJ", utf8tok::grapheme_break_property::ZWJ},
                {"Regional_Indicator", utf8tok::grapheme_break_property::RI},
                {"Prepend", utf8tok::grapheme_break_property::Prepend},
                {"SpacingMark", utf8tok::grapheme_break_property::SpacingMark},
                {"L", utf8tok::grapheme_break_property::L},
                {"V", utf8tok::grapheme_break_property::V},
                {"T", utf8tok::grapheme_break_property::T},
                {"LV", utf8tok::grapheme_break_property::LV},
                {"LVT", utf8tok::grapheme_break_property::LVT},
                {"Extended_Pictographic",utf8tok::grapheme_break_property::Extended_Pictographic},
                {"Emoji",utf8tok::grapheme_break_property::Other},
                {"Emoji_Presentation",utf8tok::grapheme_break_property::Other},
                {"Emoji_Modifier",utf8tok::grapheme_break_property::Extend},
                {"Emoji_Modifier_Base",utf8tok::grapheme_break_property::Other},
                {"Emoji_Component",utf8tok::grapheme_break_property::Other}
        };

std::string_view remove_comments(std::string_view line)
{
    for(size_t i = 0; i < line.length(); ++i)
        if(line[i] == '#')
            return line.substr(0, i);
    return line;
}

std::optional<std::pair<string_view, string_view>> split(std::string_view view, std::string_view separator)
{
    for(size_t i = 0; i < view.length(); ++i)
        if(view.compare(i,separator.length(), separator) == 0)
            return std::make_pair(view.substr(0, i), view.substr(i + separator.length()));
    return {};
}

std::string_view trim(std::string_view view)
{
    while(!view.empty() && std::isspace(view[0]))
        view.remove_prefix(1);
    while(!view.empty() && std::isspace(view[view.length() - 1]))
        view.remove_suffix(1);
    return view;
}

std::pair<code_point, code_point> parse_range(std::string_view range)
{
    auto split_result = split(range, "..");
    if(!split_result)
    {
        //Range contained no ".." separator, defines a single code point's break property
        std::string range_copy{range}; //copy string here, because P0067R5 (std::from_chars) is not supported yet and stoi needs a NULL-terminated string
        int32_t left = std::stoi(range_copy, nullptr, 16); //TODO: handle syntax errors
        return {left, left};
    }
    auto [start, end] = split_result.value();
    std::string start_copy{start};
    std::string end_copy{end};
    return {static_cast<int32_t>(std::stol(start_copy, nullptr, 16)), static_cast<int32_t>(std::stol(end_copy, nullptr, 16))};

}

int read_properties(std::ifstream stream,
                    std::vector<std::pair<code_point_range, code_point>> &grapheme_break_range_with_length)
{
    std::string line;

    while (std::getline(stream, line))
    {
        /*
         * Syntax is either [first code point in range]..[last code point in range] ; [grapheme break property]
         * or [single code point] ; [grapheme break property]
         * # starts a line comment
         */
        auto view = remove_comments(line);
        if (view.length() == 0)
            continue;

        auto tuple = split(view, ";");
        if (!tuple)
        {
            std::cerr << "Error:" << view << " is not a valid property definition:" << std::endl;
            return -1;
        }

        auto[range_view, property_name] = tuple.value();
        range_view = trim(range_view);
        property_name = trim(property_name);

        auto [range_first, range_last] = parse_range(range_view);

        auto property_name_copy = std::string(property_name); //copy to use map.find.
        if (auto it = grapheme_prop_names.find(property_name_copy); it != grapheme_prop_names.end())
        {
            code_point_range range = {range_first, it->second};
            auto it2 = std::find_if(grapheme_break_range_with_length.begin(), grapheme_break_range_with_length.end(),
                                              [&range](const std::pair<code_point_range, code_point> &gb_range){return gb_range.first.start == range.start;});

            bool already_known = it2 != grapheme_break_range_with_length.end();
            bool should_insert = !already_known || it2->first.prop == grapheme_break_property::Other;

            if(already_known && should_insert) //remove old unspecific value
                grapheme_break_range_with_length.erase(it2);

            if(should_insert)
                grapheme_break_range_with_length.emplace_back(range, range_last);
        }
        else
            std::cerr << "Could not parse input file: " << property_name_copy
                      << " is not a known grapheme break property." << std::endl;
    }
    return 0;
}


int generate_header_file(int argc, char **argv)
{
    std::vector<utf8tok::code_point_range> grapheme_break_ranges;
    std::vector<std::pair<code_point_range, code_point>> grapheme_break_range_with_length{};

    { //Read grapheme break properties
        if (argc < 2)
        {
            std::cerr << "Usage: " << argv[0] << " [path to GraphemeBreakProperty.txt] [path to emoji-data.txt] [optional: path to write graphemebreakproperty.inc to]" << std::endl;
            std::cerr
                    << "GraphemeBreakProperty.txt is available at http://www.unicode.org/Public/11.0.0/ucd/auxiliary/GraphemeBreakProperty.txt"
                    << std::endl;
            return 1;
        }


        { //Read emoji-data.txt
            std::ifstream stream{argv[2]};
            if (!stream.is_open())
            {
                std::cerr << "Failed to open " << argv[2] << ": " << strerror(errno) << std::endl;
                return 1;
            }

            if(auto result = read_properties(std::move(stream), grapheme_break_range_with_length); result != 0)
                return result;
        }

        { //Read graphemebreakproperty.txt
            std::ifstream stream{argv[1]};
            if (!stream.is_open())
            {
                std::cerr << "Failed to open " << argv[1] << ": " << strerror(errno) << std::endl;
                return 1;
            }
            if(auto result = read_properties(std::move(stream), grapheme_break_range_with_length); result != 0)
                return result;
        }
    }

    { //Write property map
        std::ofstream outputFileStream;

        if (argc == 4)
        {
            outputFileStream.open(argv[3]);
            if (!outputFileStream.is_open())
            {
                std::cerr << "Failed to open " << argv[3] << ": " << strerror(errno) << std::endl;
                return 1;
            }
        }

        std::sort(grapheme_break_range_with_length.begin(), grapheme_break_range_with_length.end(), [](auto &left, auto &right){return left.first.start < right.first.start;});

        auto size = grapheme_break_range_with_length.size() - 1;

        for(size_t i = 0; i < size; ++i) //emoji-data can insert duplicates, remove them here
        {
            auto cur = grapheme_break_range_with_length[i].first;
            auto next = grapheme_break_range_with_length[i + 1].first;
            if(cur.start != next.start)
                continue;

            if(cur.prop == grapheme_break_property::Other)
                grapheme_break_range_with_length.erase(grapheme_break_range_with_length.begin() + i);
            else if(next.prop == grapheme_break_property::Other)
                grapheme_break_range_with_length.erase(grapheme_break_range_with_length.begin() + i + 1);
            size = grapheme_break_range_with_length.size() - 1;
        }

        for(size_t i = 0; i < size; ++i)
        {
            grapheme_break_ranges.push_back(grapheme_break_range_with_length[i].first);
            if(grapheme_break_range_with_length[i].second + 1 != grapheme_break_range_with_length[i+1].first.start)
                grapheme_break_ranges.emplace_back(grapheme_break_range_with_length[i].second + 1, grapheme_break_property::Other);
        }
        grapheme_break_ranges.push_back(grapheme_break_range_with_length[size].first);
        auto &outputStream = argc == 3 ? std::cout : outputFileStream;
        outputStream
                << "std::vector<code_point_range> grapheme_break_ranges\n{\n";

        size = grapheme_break_ranges.size();
        for(size_t i = 0; i < size; ++i)
        {
            auto &range = grapheme_break_ranges[i];
            outputStream << "\t{" << range.start <<",  static_cast<grapheme_break_property>("<< range.prop << ")}";

            if (i != size - 1)
                outputStream << ",\n";
        }
        outputStream << "};";
    }
    return 0;
}
}
}
