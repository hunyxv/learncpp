cmake_minimum_required (VERSION 3.1)

project(gtest_demo)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED NO)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories("/usr/local/include") # 头文件搜索路径
link_directories("/usr/local/lib") # 库搜索路径

add_subdirectory(factorial)


# 在/usr/local/Cellar/cmake/3.24.2/share/cmake/Modules 下查找 GTest 包
find_package(GTest REQUIRED) 

add_executable(gtest_demo_1 gtest_demo_1.cpp)
target_link_libraries(gtest_demo_1 gtest)

add_executable(gtest_demo_2 gtest_demo_2.cpp)
target_include_directories(gtest_demo_2 PUBLIC "${PROJECT_SOURCE_DIR}/factorial")
target_link_libraries(gtest_demo_2 gtest factorial)

add_executable(gtest_demo_3 gtest_demo_3.cpp)
target_include_directories(gtest_demo_3 PUBLIC "${PROJECT_SOURCE_DIR}/factorial")
target_link_libraries(gtest_demo_3 gtest factorial)

add_executable(gtest_demo_4 gtest_demo_4.cpp)
target_include_directories(gtest_demo_4 PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(gtest_demo_4 gtest)
