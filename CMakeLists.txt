cmake_minimum_required(VERSION 3.10)

project(EscapeTool C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -Werror -O2)
endif()

add_executable(escape src/main.c)
