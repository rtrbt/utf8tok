#include "test_common.h"
#include <chrono>
#include <memory>
#include <numeric>


int main()
{
    std::vector<utf8tok::code_point_range> grapheme_break_ranges{};

    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream file{"./input.html"};
    std::string content { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

    size_t graphemeClusterCounter = print_grapheme_clusters(content);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "First run (includes file read):" << std::endl;
    std::cout << "Found " << graphemeClusterCounter << " grapheme clusters in " << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << "µs" << std::endl;
    std::cout << "Max cluster length is " << maxClusterLength << std::endl;

    std::vector<std::chrono::nanoseconds> times;
    times.reserve(100);
    for(int i = 0; i < 100; ++i)
    {
        start = std::chrono::high_resolution_clock::now();
        graphemeClusterCounter = print_grapheme_clusters(content);
        end = std::chrono::high_resolution_clock::now();
        times.push_back(end-start);
    }
    auto best = std::min_element(times.begin(), times.end());
    auto worst = std::max_element(times.begin(), times.end());

    std::cout << "Best: " << std::chrono::duration_cast<std::chrono::microseconds>(*best).count() << "µs" << std::endl;
    std::cout << "Worst: " << std::chrono::duration_cast<std::chrono::microseconds>(*worst).count() << "µs" << std::endl;
}