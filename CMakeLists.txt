cmake_minimum_required(VERSION 3.26)
project(ParProg)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED)


add_executable(ParProg
#        Task1.cpp
#        Task2.cpp
#        Task3.cpp
#        Task4.cpp
#        Task5.cpp
#        Task5.cpp
#        Task5.cpp
#        Task6.cpp
#        Task7.cpp
#        Task8.cpp
#        Task9.cpp
#        Task10.cpp
#        Task11.cpp
#        Task13.cpp
#        Task14.cpp
#        Task15.cpp
        MPI/MPI_task_1.cpp
        MPI/MPI_task_2.cpp
        MPI/MPI_task_3.cpp
        MPI/MPI_task_4.cpp
        MPI/MPI_task_5.cpp
)

target_compile_options(ParProg PRIVATE -Wall ${OpenMP_CXX_FLAGS})
target_link_libraries(ParProg PUBLIC MPI::MPI_CXX)
