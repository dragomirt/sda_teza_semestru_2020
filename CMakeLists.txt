cmake_minimum_required(VERSION 3.16)
project(teza_semestru_sda C)

set(CMAKE_C_STANDARD 99)

add_library(marfuri_lib lib/marfuri.c)

add_executable(teza_semestru_sda main.c)
target_link_libraries(teza_semestru_sda PRIVATE marfuri_lib)