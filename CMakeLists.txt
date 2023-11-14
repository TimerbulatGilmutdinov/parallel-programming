cmake_minimum_required(VERSION 3.26)
project(ParProg)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)
find_package(MPI REQUIRED)

add_executable(task1 OpenMP/Task1.cpp)
target_compile_options(task1 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task2 OpenMP/Task2.cpp)
target_compile_options(task1 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task3 OpenMP/Task3.cpp)
target_compile_options(task1 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task4 OpenMP/Task4.cpp)
target_compile_options(task4 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task5 OpenMP/Task5.cpp)
target_compile_options(task5 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task6 OpenMP/Task6.cpp)
target_compile_options(task6 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task7 OpenMP/Task7.cpp)
target_compile_options(task7 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task8 OpenMP/Task8.cpp)
target_compile_options(task8 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task9 OpenMP/Task9.cpp)
target_compile_options(task9 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task10 OpenMP/Task10.cpp)
target_compile_options(task10 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task11 OpenMP/Task11.cpp)
target_compile_options(task11 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task13 OpenMP/Task13.cpp)
target_compile_options(task13 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task14 OpenMP/Task14.cpp)
target_compile_options(task14 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task15 OpenMP/Task15.cpp)
target_compile_options(task15 PRIVATE -Wall ${OpenMP_CXX_FLAGS})

add_executable(task1_1 MPI/MPI_task_1_1.cpp)
target_link_libraries(task1_1 PUBLIC MPI::MPI_CXX)

add_executable(task1_2 MPI/MPI_task_1_2.cpp)
target_link_libraries(task1_2 PUBLIC MPI::MPI_CXX)

add_executable(task1_3 MPI/MPI_task_1_3.cpp)
target_link_libraries(task1_3 PUBLIC MPI::MPI_CXX)

add_executable(task1_4 MPI/MPI_task_1_4.cpp)
target_link_libraries(task1_4 PUBLIC MPI::MPI_CXX)

add_executable(task1_5 MPI/MPI_task_1_5.cpp)
target_link_libraries(task1_5 PUBLIC MPI::MPI_CXX)

add_executable(task2_1 MPI/MPI_task_2_1.cpp)
target_link_libraries(task2_1 PUBLIC MPI::MPI_CXX)

add_executable(task2_2 MPI/MPI_task_2_2.cpp)
target_link_libraries(task2_2 PUBLIC MPI::MPI_CXX)

add_executable(task2_3 MPI/MPI_task_2_3.cpp)
target_link_libraries(task2_3 PUBLIC MPI::MPI_CXX)

add_executable(task2_4 MPI/MPI_task_2_4.cpp)
target_link_libraries(task2_4 PUBLIC MPI::MPI_CXX)

add_executable(task2_5 MPI/MPI_task_2_5.cpp)
target_link_libraries(task2_5 PUBLIC MPI::MPI_CXX)

add_executable(task3_1 MPI/MPI_task_3_1.cpp)
target_link_libraries(task3_1 PUBLIC MPI::MPI_CXX)

add_executable(task3_2 MPI/MPI_task_3_2.cpp)
target_link_libraries(task3_2 PUBLIC MPI::MPI_CXX)

add_executable(task3_3 MPI/MPI_task_3_3.cpp)
target_link_libraries(task3_3 PUBLIC MPI::MPI_CXX)

add_executable(task3_4 MPI/MPI_task_3_4.cpp)
target_link_libraries(task3_4 PUBLIC MPI::MPI_CXX)

add_executable(task3_5 MPI/MPI_task_3_5.cpp)
target_link_libraries(task3_5 PUBLIC MPI::MPI_CXX)

