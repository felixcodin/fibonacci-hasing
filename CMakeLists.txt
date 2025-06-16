cmake_minimum_required(VERSION 3.10)
project(Fibonacci_Hasing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(Fibonacci_Hasing
    main.cpp
    src/fibo_hash_table.cpp
    src/mod_hash_table.cpp
    src/utils.cpp
)