cmake_minimum_required(VERSION 3.25)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp *.h)

message(${SOURCE_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
