cmake_minimum_required (VERSION 2.8.11)
add_compile_options(-std=c++11)
project (test_nntree)
find_package(Boost)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDEDIR}
    )
add_library(nnrtree NNRTree.h)
add_executable (test_nnrtree test_nnrtree.cpp)
target_link_libraries (test_nnrtree nnrtree)
set_target_properties(nnrtree PROPERTIES LINKER_LANGUAGE CXX)


