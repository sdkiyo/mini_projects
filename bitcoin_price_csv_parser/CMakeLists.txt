cmake_minimum_required(VERSION 3.31.7)

project( csv_parser
	LANGUAGES C )

set(CMAKE_C_STANDARD 23)

add_library(lib_parser SHARED parser.c)
set_target_properties(lib_parser PROPERTIES
	PREFIX "lib_"
	OUTPUT_NAME "csv_parser"
	SUFFIX ".so")


add_executable(${PROJECT_NAME} main.c)
