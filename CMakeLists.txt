cmake_minimum_required(VERSION 3.30)
project(IntegralSolver C)

set(CMAKE_C_STANDARD 23)

add_executable(IntegralSolver main.c
        main.h
        math.c
        math.h)
target_link_libraries(IntegralSolver m)
