cmake_minimum_required(VERSION 3.30)
project(IntegralSolver C)

set(CMAKE_C_STANDARD 23)

add_executable(IntegralSolver main.c
        math.c
        math.h
        tokenizer.c
        tokenizer.h
        commons.h
        process_tokens.c
        process_tokens.h)

target_link_libraries(IntegralSolver m)
