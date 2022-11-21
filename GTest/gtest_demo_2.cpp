#include <gtest/gtest.h>
#include "factorial/factorial.h"

int main() {
    EXPECT_EQ(1, Factorial(-5));  // 测试计算负数的阶乘
    EXPECT_EQ(1, Factorial(0));   // 测试计算0的阶乘
    EXPECT_EQ(6, Factorial(3));   // 测试计算正数的阶乘
    EXPECT_EQ(-1, Factorial(6));  // 测试错误的示例
    return 0;
}