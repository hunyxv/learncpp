# pkg-config

## 简单的示例

首先编写一个库文件，目录结构如下：

```Plain Text
mymath.             # 库的顶层目录
├── include         # 库提供的头文件目录
│   └── mymath.h    # 库提供的头文件
├── lib             # 库文件目录
│   └── libmymath.a # 生成的库文件
├── mymath.cpp      # 源文件
└── mymath.pc       # .pc文件，以便pkg-config使用
```

库文件提供的内容很简单：一个add接口用于计算两个整数的和并打印出来。由于是使用库的方式，mymath.cpp文件只是在编译libmymath.a时需要使用，并不需要对外提供.

编译生成静态库文件:

```shell
g++ -c mymath.cpp -o
ar cqs ./lib/libmymath.a mymath.o
```

## .pc文件的编写

头文件和库文件所在的目录根据实际指定即可，此处以/XXX代替.

```Plain Text
librootdir=/Users/xxx/Projects/learncpp/testpkg/mymath # 项目所在绝对路径

Name: mymath
Description: a simple add function
Version: 1.0
Cflags: -I${librootdir}/include
Libs: -L${librootdir}/lib -lmymath
```

## 让.pc文件被 pkg-config 可见

可以把 mymath.pc 拷贝到系统查找目录（`/usr/lib/pkgconfig`, `/usr/share/pkgconfig`, `/usr/local/lib/pkgconfig`, `/usr/local/share/pkgconfig`）或者将 mymath.pc 文件所在的目录添加到环境变量 `PKG_CONFIG_PATH` 中，此处使用第二种办法：

```shell
# 命令行中执行，或直接写在 .zshrc or .bashrc 文件中
PKG_CONFIG_PATH=/Users/hongyu/Projects/cpp/mymath
export PKG_CONFIG_PATH
```

这样就可以使用pkg-config命令来获取mymath库的信息了：

```shell
# 命令行中执行
pkg-config --list-all | grep "mymath"
mymath            mymath - a simple add function

pkg-config --cflags --libs mymath
-I/XXX/mymath/include -L/XXX/mymath/lib -lmymath
```

## 使用 pkg-config

```shell
g++ -o main main.cpp `pkg-config --cflags --libs mymath`
```