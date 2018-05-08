project(EigenJl)
cmake_minimum_required(VERSION 2.8.12)

find_package(JlCxx REQUIRED)

set(CMAKE_INSTALL_RPATH "${JlCxx_DIR}/../")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("${CMAKE_SOURCE_DIR}/../../eigen3/")
add_library(eigenjl SHARED eigenjl.cpp)
target_link_libraries(eigenjl JlCxx::cxxwrap_julia)
