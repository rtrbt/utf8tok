cmake_minimum_required(VERSION 3.9)
project(utf8tok)

set(CMAKE_CXX_STANDARD 17)

option(USE_CLANG "build application with clang" OFF)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(USE_CLANG)
    set(CMAKE_C_COMPILER "/usr/bin/clang")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector-strong -fPIC")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c++98-c++11-compat-pedantic")
else()
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pie -rdynamic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wpedantic")
endif()

set(CMAKE_CXX_FLAGS_RELEASE " ${CMAKE_CXX_FLAGS_RELEASE} -march=x86-64 -mtune=generic -O3 -pipe -fvisibility-inlines-hidden -fno-exceptions -fno-rtti")
set(CMAKE_CXX_FLAGS_MINSIZEREL " ${CMAKE_CXX_FLAGS_MINSIZEREL} -march=x86-64 -mtune=generic -Os -pipe -fvisibility-inlines-hidden -fno-exceptions -fno-rtti")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO " ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -march=x86-64 -mtune=generic -Os -pipe -fvisibility-inlines-hidden -fno-exceptions -fno-rtti")

set(GENERATOR_SOURCE_FILES src/generator.h src/generator.cpp)
add_executable(utf8tok_generator ${GENERATOR_SOURCE_FILES})

set(TEST_SOURCE_FILES src/test.cpp utf8tok.h)
add_executable(utf8tok_test ${TEST_SOURCE_FILES})

set(BENCHMARK_SOURCE_FILES src/benchmark.cpp utf8tok.h)
add_executable(utf8tok_benchmark ${BENCHMARK_SOURCE_FILES})