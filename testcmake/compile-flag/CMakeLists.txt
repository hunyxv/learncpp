cmake_minimum_required(VERSION 3.5)

# 设置默认的C++的编译标志
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

# 设置项目名称
project (compile_flags)

# 添加可执行文件
add_executable(cmake_examples_compile_flags main.cpp)

# 对可执行二进制文件添加编译标志
target_compile_definitions(cmake_examples_compile_flags 
    PRIVATE EX3
)
