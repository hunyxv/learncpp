cmake_minimum_required(VERSION 3.5)

# 设置项目名
project (cf_example)

# 设置项目版本
set (cf_example_VERSION_MAJOR 0)
set (cf_example_VERSION_MINOR 2)
set (cf_example_VERSION_PATCH 1)
set (cf_example_VERSION "${cf_example_VERSION_MAJOR}.${cf_example_VERSION_MINOR}.${cf_example_VERSION_PATCH}")

# configure_file()函数输入ver.h.in，通过编译就可以在  ${PROJECT_BINARY_DIR} 目录下生成ver.h
# ver.in.h文件中将 版本号赋值给 常量ver
configure_file(ver.h.in ${PROJECT_BINARY_DIR}/ver.h)

# configure_file()函数输入path.h.in，通过编译就可以在  ${PROJECT_BINARY_DIR} 目录下生成path.h
configure_file(path.h.in ${PROJECT_BINARY_DIR}/path.h @ONLY)

# 添加可执行文件
add_executable(cf_example main.cpp)

# 将新生成的文件以 PUBLIC 方式添加在 include 目录中
target_include_directories(cf_example
    PUBLIC
        ${CMAKE_BINARY_DIR}
)