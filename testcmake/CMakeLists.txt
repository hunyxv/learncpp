cmake_minimum_required (VERSION 3.1)
project (CalculateSqrt)

option(USE_MYMATH "Use tutorial provided math implementation" ON) 

# 设置两个版本号变量
set (CalculateSqrt_VERSION_MAJOR 1)
set (CalculateSqrt_VERSION_MINOR 0)
# specify the C++ standard 
set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 

# 配置一个头文件来传递一些CMake设置到源代码
# configure_file的作用将一份文件拷贝到另一个位置并修改它的内容，使得在代码中使用CMake中定义的变量 
# configure_file官方文档：https://cmake.org/cmake/help/latest/command/configure_file.html 
configure_file (
    "${PROJECT_SOURCE_DIR}/CalculateSqrtConfig.h.in"
    "${PROJECT_BINARY_DIR}/CalculateSqrtConfig.h"
)

if(USE_MYMATH) 
    # add the MathFunctions library,Add a subdirectory to the build，将新加的子目录用于build 
    add_subdirectory(MathFunctions) 
    list(APPEND EXTRA_LIBS MathFunctions) 
    # list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")
    # 使用 set 命令也可以
    set(EXTRA_INCLUDES ${EXTRA_INCLUDES} "${PROJECT_SOURCE_DIR}/MathFunctions")
endif(USE_MYMATH) 

# 添加目标可执行文件
add_executable(CalculateSqrt calculatesqrt.cpp) 
# 该指令的作用为将目标文件与库文件进行链接 
# target_link_libraries官方文档:https://cmake.org/cmake/help/latest/command/target_link_libraries.html 
target_link_libraries(CalculateSqrt "${EXTRA_LIBS}")

# 指定项目编译的时候需要include的文件路径，PROJECT_BINARY_DIR变量为编译发生的目录，也就是make执行的目录，PROJECT_SOURCE_DIR为工程所在的目录 
# target_include_directories官方文档：https://cmake.org/cmake/help/v3.3/command/target_include_directories.html 
target_include_directories(CalculateSqrt PUBLIC 
                           "${PROJECT_BINARY_DIR}" 
                           "${EXTRA_INCLUDES}")

# add the install targets
install (TARGETS CalculateSqrt DESTINATION bin)
# CalculateSqrt 项目没有 CalculateSqrt.h
# install (FILES "${PROJECT_BINARY_DIR}/CalculateSqrt.h" DESTINATION include)


include(CTest)

# # does the application run
# add_test (CalculateSqrtRuns CalculateSqrt 25)

# # does it sqrt of 25
# add_test (CalculateSqrtComp25 CalculateSqrt 25)
# set_tests_properties (CalculateSqrtComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")

# # does it handle negative numbers
# add_test (CalculateSqrtNegative CalculateSqrt -25)
# set_tests_properties (CalculateSqrtNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is 0")

# # does it handle small numbers
# add_test (CalculateSqrtSmall CalculateSqrt 0.0001)
# set_tests_properties (CalculateSqrtSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")

# # does the usage message work?
# add_test (CalculateSqrtUsage CalculateSqrt)
# set_tests_properties (CalculateSqrtUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

#define a macro to simplify adding tests, then use it
macro (do_test arg result)
  add_test (CalculateSqrt${arg} CalculateSqrt ${arg})
  set_tests_properties (CalculateSqrt${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)
 
# do a bunch of result based tests
do_test (25 "25 is 5")
do_test (-25 "-25 is 0")
do_test (0.0001 "0.0001 is 0.01")