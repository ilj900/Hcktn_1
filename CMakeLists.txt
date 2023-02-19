cmake_minimum_required(VERSION 3.13)

project(Hcktn_1)

set(CMAKE_CXX_STANDARD 17)


include_directories(
        include)


set(SOURCE
        src/main.cpp)

set(INCLUDE
		include/main.h)

add_executable(Hcktn_1 ${SOURCE} ${INCLUDE})
