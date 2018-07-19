#pragma once
#define UTF8TOK_IMPLEMENTATION
#include "../utf8tok.h"
#include <chrono>
#include <memory>
#include <numeric>

const size_t scratchBufferSize = 10;
std::unique_ptr<uint8_t[]> scratchBuffer = std::make_unique<uint8_t[]>(scratchBufferSize * (sizeof(utf8tok::code_point) + sizeof(utf8tok::grapheme_break_property)));

size_t maxClusterLength = 0;
size_t print_grapheme_clusters(std::string_view str)
{
    size_t graphemeClusterCounter = 0;
    std::string_view graphemeCluster = *utf8tok::next_grapheme_cluster(str, reinterpret_cast<uint8_t *>(scratchBuffer.get()), scratchBufferSize * sizeof(utf8tok::code_point));
    maxClusterLength = graphemeCluster.length();
    while(graphemeCluster.length() > 0)
    {
        //std::cout << graphemeCluster << std::endl;
        ++graphemeClusterCounter;
        graphemeCluster = *utf8tok::next_grapheme_cluster(str, reinterpret_cast<uint8_t *>(scratchBuffer.get()), scratchBufferSize * sizeof(utf8tok::code_point));
        maxClusterLength = std::max(maxClusterLength, graphemeCluster.length());
    }
    return graphemeClusterCounter;
}

size_t code_point_count(utf8tok::grapheme_cluster_view cluster)
{
    size_t result = 0;
    while(!cluster.empty())
    {
        utf8tok::next_code_point(cluster);
        ++result;
    }
    return result;
}


utf8tok::code_point next_code_point(std::vector<utf8tok::code_point> &testCodepoints)
{
    auto result = testCodepoints[0];
    testCodepoints.erase(testCodepoints.begin());
    return result;
}

size_t remove_cluster(std::vector<utf8tok::code_point> &testCodepoints)
{
    size_t code_point_count = 1;
    auto maxCodePoints = scratchBufferSize; //hold back memory for grapheme break properties;
    utf8tok::array_view<utf8tok::code_point> left_code_points{scratchBuffer.get(), maxCodePoints};
    utf8tok::array_view<utf8tok::grapheme_break_property> left_props{scratchBuffer.get() + maxCodePoints * sizeof(utf8tok::code_point), maxCodePoints};
    size_t codePointCount = 0;


    utf8tok::code_point right_cp = next_code_point(testCodepoints);

    if(codePointCount >= left_code_points.size)
        return std::numeric_limits<size_t>::max();
    left_code_points[codePointCount++] = right_cp;
    if(testCodepoints.empty())
        return code_point_count;
    auto copy = testCodepoints;
    right_cp = next_code_point(copy);

    while(right_cp != -1 && !utf8tok::is_grapheme_cluster_boundary(left_code_points, codePointCount, right_cp, left_props))
    {
        if(codePointCount >= left_code_points.size)
            return std::numeric_limits<size_t>::max();
        left_code_points[codePointCount++] = right_cp;

        testCodepoints = copy;
        ++code_point_count;
        if(copy.empty())
            break;
        right_cp = next_code_point(copy);
    }
    return code_point_count;
}

std::vector<size_t> segmentate(std::vector<utf8tok::code_point> testCodepoints)
{
    std::vector<size_t> result{};

    while(!testCodepoints.empty())
    {
        result.push_back(remove_cluster(testCodepoints));
    }

    return result;
}