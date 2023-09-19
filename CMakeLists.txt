cmake_minimum_required(VERSION 3.26)
project(ParProg)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(ParProg
        Task1.cpp
        Task2.cpp
        Task3.cpp
        Task4.cpp
        Task5.cpp
        Task5.cpp
        Task5.cpp
)

target_compile_options(ParProg PRIVATE -Wall ${OpenMP_CXX_FLAGS})
target_link_libraries(ParProg PRIVATE ${OpenMP_CXX_FLAGS})
