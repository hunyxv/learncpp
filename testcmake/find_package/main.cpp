#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Hello Third Party Include!" << std::endl;

    // new一个智能指针
    boost::shared_ptr<int> isp(new int(4));

    // boost文件系统的简单调用
    boost::filesystem::path path = "/usr/share/cmake/modules";
    if (path.is_relative()) {
        std::cout << "Path is relative" << std::endl;
    } else {
        std::cout << "Path is not relative" << std::endl;
    }

    return 0;
}