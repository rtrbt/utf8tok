#ifdef UTF8TOK_IMPLEMENTATION
#undef UTF8TOK_IMPLEMENTATION

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cassert>
#include <algorithm>
#include <string_view>
#include <unordered_map>
#include <cstring>

namespace utf8tok
{
using string_view = std::string_view;
using grapheme_cluster_view = string_view;
using code_point_view = string_view;
using code_point = int32_t;

enum grapheme_break_property : uint8_t
{
    CR,
    LF,
    Control,
    Extend,
    ZWJ,
    RI,
    Prepend,
    SpacingMark,
    L,
    V,
    T,
    LV,
    LVT,
    Extended_Pictographic,
    Start_of_text,
    End_of_text,
    Other
};

template<typename TElement>
struct array_view
{
    TElement* data;
    const size_t size;

    array_view(uint8_t *data, size_t elementCount) : data(reinterpret_cast<TElement*>(data)), size(elementCount)
    {
        ::memset(data, 0, size * sizeof(TElement));
    }

    TElement &operator[](size_t index)
    {
#ifndef NDEBUG
        if(index > size)
        {
            std::cerr << "Index " << index << " out of range for array " << data << " of size " << size << std::endl;
            exit(1);
        }
#endif
        return data[index];
    }

    TElement* begin()
    {
        return data;
    }

    TElement* end()
    {
        return data + size;
    }
};

/**
 * Represents a range of code points and their corresponding grapheme_break_property.
 */
struct code_point_range
{
    code_point_range(code_point p_start, grapheme_break_property p_prop) : start(p_start), prop(p_prop) {}

    code_point start : 24;
    grapheme_break_property prop : 8;
};

/**
 * Defined in graphemebreakproperty.inc
 */
extern std::vector<code_point_range> grapheme_break_ranges;

/**
 * Returns a code_point_view containing only the next code point (1 to 4 bytes)
 */
code_point_view next_code_point(string_view &str);

/**
 * Decodes the given code point
 * @param view View containing one code point only.
 * @return Decoded code point or -1 if given view was to long.
 */
code_point decode_code_point(code_point_view view);

/**
 * Returns the grapheme break property for the given code point.
 */
grapheme_break_property get_prop(code_point codepoint);

/**
 * Returns whether there is a grapheme cluster boundary between the last of the given left and the right code point.
 * @param left_code_points Already found code points of the grapheme cluster.
 * @param left_code_point_count Count of valid left code points
 * @param right_code_point Code point right of the possible boundary
 * @param leftProps grapheme break properties of the already found code points.
 * @return True iff there is a grapheme cluster boundary between the last left and the right code point, false otherwise.
 */
bool is_grapheme_cluster_boundary(array_view<code_point> left_code_points, size_t left_code_point_count, code_point right_code_point, array_view<grapheme_break_property>leftProps);

/**
 * Returns the next grapheme cluster or std::nullopt if the given scratch buffer was too small.
 * @param str_view String view to search the next cluster in. If a cluster was found (i.e. the scratch buffer's size was sufficient), it will be removed from the view.
 * @param scratchBuffer A buffer to store temporary variables, which are not needed after one call of next_grapheme_cluster. ~ 50 bytes are sufficient for most grapheme clusters.
 * @param scratchBufferSize Size of the scratch buffer
 * @return The next grapheme cluster or std::nullopt if the given scratch buffer was too small.
 */
std::optional<grapheme_cluster_view> next_grapheme_cluster(string_view &str_view, uint8_t* scratchBuffer, size_t scratchBufferSize);


code_point_view next_code_point(string_view &str)
{
    size_t length = 0;
    //11110xxx - 4
    //1110xxxx - 3
    //110xxxxx - 2
    //10xxxxxx - code point continuation marker
    //0xxxxxxx - 1
    if((str[0] & 0b1111'0000) == 0b1111'0000)
        length = 4;
    else if((str[0] & 0b1110'0000) == 0b1110'0000)
        length = 3;
    else if((str[0] & 0b1100'0000) == 0b1100'0000)
        length = 2;
    else if((str[0] & 0b1000'0000) == 0b1000'0000)
        return {}; //0b10... is the code point continuation marker
    else
        length = 1;
    if(str.length() < length)
        return {};

    string_view result{str.data(), length};
    str.remove_prefix(length);
    return result;
}

code_point decode_code_point(code_point_view view)
{
    if(view.length() == 1)
        return view[0];
    if(view.length() == 2)
        return ((view[0] & 0b0001'1111) << 6) | (view[1] & 0b0011'1111);
    if(view.length() == 3)
        return ((view[0] & 0b0000'1111) << 12) | ((view[1] & 0b0011'1111) << 6) | (view[2] & 0b0011'1111);
    if(view.length() == 4)
        return ((view[0] & 0b0000'0111) << 18) | ((view[1] & 0b0011'1111) << 12) | ((view[2] & 0b0011'1111) << 6) | (view[3] & 0b0011'1111);
    return -1;
}

grapheme_break_property get_prop(code_point codepoint)
{
    for(size_t i = 0; i < grapheme_break_ranges.size() - 1; ++i)
        if(grapheme_break_ranges[i].start <= codepoint && codepoint < grapheme_break_ranges[i+1].start)
            return grapheme_break_ranges[i].prop;

    return grapheme_break_ranges[grapheme_break_ranges.size() - 1].prop;
}

bool is_grapheme_cluster_boundary(array_view<code_point> left_code_points, size_t left_code_point_count, code_point right_code_point, array_view<grapheme_break_property>leftProps)
{
    auto lastLeftProp = left_code_point_count == 0 ?
                        grapheme_break_property::Start_of_text :
                        get_prop(left_code_points[left_code_point_count - 1]);
    leftProps[left_code_point_count - 1] = lastLeftProp;

    auto rightProp = get_prop(right_code_point);

    //GB1
    if (lastLeftProp == grapheme_break_property::Start_of_text && rightProp != End_of_text)
        return true;

    //GB2
    if (lastLeftProp != grapheme_break_property::Start_of_text && rightProp == End_of_text)
        return true;

    //GB3
    if (lastLeftProp == grapheme_break_property::CR && rightProp == grapheme_break_property::LF)
        return false;

    //GB4
    if (lastLeftProp == Control || lastLeftProp == CR || lastLeftProp == LF)
        return true;

    //GB5
    if (rightProp == Control || rightProp == CR || rightProp == LF)
        return true;

    //GB6
    if (lastLeftProp == L
        && (rightProp == L
            || rightProp == V
            || rightProp == LV
            || rightProp == LVT))
        return false;

    //GB7
    if ((lastLeftProp == LV || lastLeftProp == V) && (rightProp == V || rightProp == T))
        return false;

    //GB8
    if ((lastLeftProp == LVT || lastLeftProp == T) && rightProp == T)
        return false;

    //GB9
    if (rightProp == Extend || rightProp == ZWJ)
        return false;

    //GB9a
    if (rightProp == SpacingMark)
        return false;

    //GB9b
    if (lastLeftProp == Prepend)
        return false;

    //GB11
    bool starts_with_ext_pic = leftProps[0] == Extended_Pictographic;
    bool all_intermediate_are_extend = std::all_of(leftProps.begin() + 1, leftProps.begin()  + left_code_point_count - 1, [](const grapheme_break_property &prop){return prop == Extend;});

    if(starts_with_ext_pic && all_intermediate_are_extend &&
       lastLeftProp == ZWJ && rightProp == Extended_Pictographic)
        return false;

    //GB12+GB13
    int regionalIndicatorCounter = 0;
    auto it = leftProps.begin() + left_code_point_count - 1;

    while(it != leftProps.begin() && *it == RI)
    {
        ++regionalIndicatorCounter;
        --it;
    }
    if(*it == RI)
    {
        ++regionalIndicatorCounter;
    }
    if(regionalIndicatorCounter % 2 == 1 && rightProp == RI)
        return false;

    //GB999
    return true;
}

std::optional<grapheme_cluster_view> next_grapheme_cluster(string_view &str_view, uint8_t* scratchBuffer, size_t scratchBufferSize)
{
    const string_view immutable_copy = str_view;
    string_view cluster{str_view.data(), 0};

    auto maxCodePoints = scratchBufferSize / (sizeof(code_point) + sizeof(grapheme_break_property)); //reserve memory for grapheme break properties;
    array_view<code_point> left_code_points{scratchBuffer, maxCodePoints};
    array_view<grapheme_break_property> left_props{scratchBuffer + maxCodePoints * sizeof(code_point), maxCodePoints};
    size_t codePointCount = 0;

    auto next_cp = next_code_point(str_view);

    code_point right_cp = decode_code_point(next_cp);
    cluster = string_view{cluster.data(), cluster.length() + next_cp.length()};

    if(codePointCount >= left_code_points.size)
    {
        str_view = immutable_copy;
        return std::nullopt;
    }
    left_code_points[codePointCount++] = right_cp;

    auto copy = str_view;
    next_cp = next_code_point(copy);
    right_cp = decode_code_point(next_cp);

    while(right_cp != -1 && !is_grapheme_cluster_boundary(left_code_points, codePointCount, right_cp, left_props))
    {
        if(codePointCount >= left_code_points.size)
        {
            str_view = immutable_copy;
            return std::nullopt;
        }
        left_code_points[codePointCount++] = right_cp;
        cluster = string_view{cluster.data(), cluster.length() + next_cp.length()};
        str_view = copy;

        next_cp = next_code_point(copy);
        right_cp = decode_code_point(next_cp);
    }
    return cluster;
}
#include "graphemebreakproperty.inc"
}
#else
#ifndef INCLUDE_UTF8TOK_H
#define INCLUDE_UTF8TOK_H

namespace utf8tok
{
extern code_point get_code_point(code_point_view view);
extern code_point_view next_code_point(string_view &str);
extern grapheme_cluster_view next_grapheme_cluster(string_view &str_view);
extern grapheme_break_property get_prop(code_point codepoint);
}

#endif
#endif //UTF8TOK_IMPLEMENTATION
