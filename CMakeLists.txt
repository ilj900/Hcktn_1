cmake_minimum_required(VERSION 3.25)
project(Hackaton
    VERSION 0.1
    DESCRIPTION "Super cool application")

set(CMAKE_CXX_STANDARD 20)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/Install CACHE PATH "Set Install prefix to default" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

add_subdirectory(Sources)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
