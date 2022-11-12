# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# 如果编译类型未指定，那么就设置默认编译类型
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    # message 可用于在编译 cmak e时打印信息，比如我们想打印出 `PROJECT_SOURCE_DIR` 这个变量，就可以按下面这行代码
    # message("PROJECT_SOURCE_DIR value is ${PROJECT_SOURCE_DIR}")   -- 打印`PROJECT_SOURCE_DIR`变量的值
    message("Setting build type to 'RelWithDebInfo' as none was specified.")
    # 给CMAKE_BUILD_TYPE变量赋值为 RelWithDebInfo ，并将这个值写入缓存，并覆盖缓存中该变量之前的值(如果有的话)。
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
    # 当使用cmake-gui的时候，设置编译类型的四个可选项
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
        "MinSizeRel" "RelWithDebInfo")
endif()

# 设置项目名称
project (build_type)

# 添加可执行文件
add_executable(cmake_examples_build_type main.cpp)
