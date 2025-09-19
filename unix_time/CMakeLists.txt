cmake_minimum_required(VERSION 3.31.7)

project( unix_time
	VERSION 0.0.0
	LANGUAGES C )

set ( CMAKE_C_STANDARD 23 )

add_executable( ${PROJECT_NAME} main.c unix_time.c )
