cmake_minimum_required(VERSION 3.5)

# 项目名
project (third_party_include)

# 找到 boost 的特定版本，COMPONENTS后面罗列的是 boost 的一些子模块
find_package(Boost 1.46.1 REQUIRED COMPONENTS filesystem system)

# 检查是否找到
if(Boost_FOUND)
    message ("boost found")
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

# 添加可执行文件
add_executable(third_party_include main.cpp)

# 将第三方库某模块链接到可执行文件
target_link_libraries( third_party_include
    PRIVATE
        Boost::filesystem
)