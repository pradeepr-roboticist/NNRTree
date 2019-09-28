cmake_minimum_required (VERSION 2.8.11)
add_compile_options(-std=c++11)
project (test_nntree)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(nnrtree NNRTree.cpp NNRTree.h)
add_executable (test_nnrtree test_nnrtree.cpp)
target_link_libraries (test_nnrtree nnrtree)

