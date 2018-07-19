#include "test_common.h"
#include <chrono>
#include <memory>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

namespace doctest
{
    template <typename T>
    struct StringMaker<std::vector<T> >
    {
        static String convert(const std::vector<T>& in) {
            std::ostringstream oss;

            oss << "[";
            for(typename std::vector<T>::const_iterator it = in.begin(); it != in.end(); ++it)
                oss << *it << ", ";
            oss << "]";

            return oss.str().c_str();
        }
    };
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000020,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000020,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000020,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000020,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000020,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000020,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000020,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000020,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000020,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) × [3.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000000d,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000000d,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000000d,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000000d,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000000d,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000d,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000d,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000000a,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000000a,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000000a,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000000a,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000000a,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000000a,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x00000001,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x00000001,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x00000001,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x00000001,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000001,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <START OF HEADING> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x00000001,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000034f,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000034f,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000034f,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000034f,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000034f,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000034f,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000034f,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000034f,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000034f,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAPHEME JOINER (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000034f,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0001f1e6,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0001f1e6,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [12.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0001f1e6,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0001f1e6,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0001f1e6,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0001f1e6,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0001f1e6,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0001f1e6,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0001f1e6,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0001f1e6,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f1e6,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.2] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000600,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000600,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000600,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000600,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.2] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000600,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.2] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.2] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.2] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.2] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.2] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.2] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000600,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000600,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.2] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000600,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000600,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC NUMBER SIGN (Prepend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000600,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000903,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000903,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000903,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000903,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000903,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000903,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000903,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000903,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000903,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] DEVANAGARI SIGN VISARGA (SpacingMark) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000903,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001100,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001100,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001100,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001100,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001100,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00001100,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001100,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001100,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001100,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00001100,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [6.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001100,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [6.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001100,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001100,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [6.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001100,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [6.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001100,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001100,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001100,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00001100,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001100,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00001100,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001100,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001100,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001100,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001160,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00001160,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001160,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00001160,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [7.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001160,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [7.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001160,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001160,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00001160,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001160,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00001160,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00001160,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JUNGSEONG FILLER (V) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00001160,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x000011a8,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x000011a8,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x000011a8,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x000011a8,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [8.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x000011a8,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x000011a8,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x000011a8,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x000011a8,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x000011a8,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x000011a8,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL JONGSEONG KIYEOK (T) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x000011a8,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000ac00,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000ac00,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000ac00,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000ac00,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [7.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000ac00,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [7.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000ac00,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000ac00,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000ac00,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000ac00,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000ac00,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac00,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000ac01,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000ac01,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000ac01,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000ac01,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [8.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000ac01,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000ac01,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000ac01,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000ac01,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000ac01,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000ac01,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000231a,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000231a,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000231a,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000231a,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000231a,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000231a,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000231a,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000231a,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000231a,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] WATCH (ExtPict) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000231a,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000300,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000300,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000300,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000300,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000300,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000300,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000300,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000300,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000300,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000300,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000200d,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000200d,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000200d,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000200d,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000200d,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000200d,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x0000200d,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0000200d,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000200d,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000200d,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000378,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000378,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000378,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000378,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000378,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000378,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000378,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00000378,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x00000378,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <reserved-0378> (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000378,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <CARRIAGE RETURN (CR)> (CR) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x0000000d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x0000000a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <START OF HEADING> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x00000001};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAPHEME JOINER (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000d800,0x00000308,0x0000034f};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x0001f1e6};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x00000600};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000d800,0x00000308,0x00000903};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JUNGSEONG FILLER (V) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x00001160};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL JONGSEONG KIYEOK (T) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x000011a8};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GA (LV) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x0000ac00};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] HANGUL SYLLABLE GAG (LVT) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x0000ac01};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] WATCH (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x0000231a};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] COMBINING GRAVE ACCENT (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000d800,0x00000308,0x00000300};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x0000d800,0x00000308,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] <reserved-0378> (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x00000378};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1};
    std::vector<int> input{0x0000d800,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <surrogate-D800> (Control) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [5.0] <surrogate-D800> (Control) ÷ [0.3]")
{
    std::vector<size_t> expected{1,1,1};
    std::vector<int> input{0x0000d800,0x00000308,0x0000d800};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] <CARRIAGE RETURN (CR)> (CR) × [3.0] <LINE FEED (LF)> (LF) ÷ [4.0] LATIN SMALL LETTER A (Other) ÷ [5.0] <LINE FEED (LF)> (LF) ÷ [4.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1,1,1};
    std::vector<int> input{0x0000000d,0x0000000a,0x00000061,0x0000000a,0x00000308};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000061,0x00000308};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] SPACE (Other) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] ARABIC LETTER NOON (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000020,0x0000200d,0x00000646};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] ARABIC LETTER NOON (Other) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] SPACE (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000646,0x0000200d,0x00000020};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL CHOSEONG KIYEOK (L) × [6.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00001100,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GA (LV) × [7.0] HANGUL JONGSEONG KIYEOK (T) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac00,0x000011a8,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] HANGUL SYLLABLE GAG (LVT) × [8.0] HANGUL JONGSEONG KIYEOK (T) ÷ [999.0] HANGUL CHOSEONG KIYEOK (L) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0000ac01,0x000011a8,0x00001100};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [12.0] REGIONAL INDICATOR SYMBOL LETTER B (RI) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER C (RI) ÷ [999.0] LATIN SMALL LETTER B (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1,1};
    std::vector<int> input{0x0001f1e6,0x0001f1e7,0x0001f1e8,0x00000062};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [13.0] REGIONAL INDICATOR SYMBOL LETTER B (RI) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER C (RI) ÷ [999.0] LATIN SMALL LETTER B (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2,1,1};
    std::vector<int> input{0x00000061,0x0001f1e6,0x0001f1e7,0x0001f1e8,0x00000062};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [13.0] REGIONAL INDICATOR SYMBOL LETTER B (RI) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER C (RI) ÷ [999.0] LATIN SMALL LETTER B (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,3,1,1};
    std::vector<int> input{0x00000061,0x0001f1e6,0x0001f1e7,0x0000200d,0x0001f1e8,0x00000062};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER B (RI) × [13.0] REGIONAL INDICATOR SYMBOL LETTER C (RI) ÷ [999.0] LATIN SMALL LETTER B (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2,2,1};
    std::vector<int> input{0x00000061,0x0001f1e6,0x0000200d,0x0001f1e7,0x0001f1e8,0x00000062};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER A (RI) × [13.0] REGIONAL INDICATOR SYMBOL LETTER B (RI) ÷ [999.0] REGIONAL INDICATOR SYMBOL LETTER C (RI) × [13.0] REGIONAL INDICATOR SYMBOL LETTER D (RI) ÷ [999.0] LATIN SMALL LETTER B (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2,2,1};
    std::vector<int> input{0x00000061,0x0001f1e6,0x0001f1e7,0x0001f1e8,0x0001f1e9,0x00000062};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [0.3]")
{
    std::vector<size_t> expected{2};
    std::vector<int> input{0x00000061,0x0000200d};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) ÷ [999.0] LATIN SMALL LETTER B (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000061,0x00000308,0x00000062};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) × [9.1] DEVANAGARI SIGN VISARGA (SpacingMark) ÷ [999.0] LATIN SMALL LETTER B (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000061,0x00000903,0x00000062};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) ÷ [999.0] ARABIC NUMBER SIGN (Prepend) × [9.2] LATIN SMALL LETTER B (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{1,2};
    std::vector<int> input{0x00000061,0x00000600,0x00000062};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] BABY (ExtPict) × [9.0] EMOJI MODIFIER FITZPATRICK TYPE-6 (Extend) ÷ [999.0] BABY (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x0001f476,0x0001f3ff,0x0001f476};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) × [9.0] EMOJI MODIFIER FITZPATRICK TYPE-6 (Extend) ÷ [999.0] BABY (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000061,0x0001f3ff,0x0001f476};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) × [9.0] EMOJI MODIFIER FITZPATRICK TYPE-6 (Extend) ÷ [999.0] BABY (ExtPict) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [11.0] OCTAGONAL SIGN (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,3};
    std::vector<int> input{0x00000061,0x0001f3ff,0x0001f476,0x0000200d,0x0001f6d1};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] BABY (ExtPict) × [9.0] EMOJI MODIFIER FITZPATRICK TYPE-6 (Extend) × [9.0] COMBINING DIAERESIS (Extend_ExtCccZwj) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [11.0] BABY (ExtPict) × [9.0] EMOJI MODIFIER FITZPATRICK TYPE-6 (Extend) ÷ [0.3]")
{
    std::vector<size_t> expected{6};
    std::vector<int> input{0x0001f476,0x0001f3ff,0x00000308,0x0000200d,0x0001f476,0x0001f3ff};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] OCTAGONAL SIGN (ExtPict) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [11.0] OCTAGONAL SIGN (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x0001f6d1,0x0000200d,0x0001f6d1};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] OCTAGONAL SIGN (ExtPict) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000061,0x0000200d,0x0001f6d1};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] UPPER BLADE SCISSORS (Other) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) × [11.0] UPPER BLADE SCISSORS (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{3};
    std::vector<int> input{0x00002701,0x0000200d,0x00002701};
            CHECK(expected == segmentate(input));
}

TEST_CASE("  ÷ [0.2] LATIN SMALL LETTER A (Other) × [9.0] ZERO WIDTH JOINER (ZWJ_ExtCccZwj) ÷ [999.0] UPPER BLADE SCISSORS (Other) ÷ [0.3]")
{
    std::vector<size_t> expected{2,1};
    std::vector<int> input{0x00000061,0x0000200d,0x00002701};
            CHECK(expected == segmentate(input));
}

