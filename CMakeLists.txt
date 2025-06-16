cmake_minimum_required(VERSION 3.10)
project(FiboHashing)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(FiboHashing
    main.cpp
    src/FiboHashTable.cpp
    src/ModHashTable.cpp
)

add_executable(TestHashing
    test/test.cpp
    src/FiboHashTable.cpp
    src/ModHashTable.cpp
)