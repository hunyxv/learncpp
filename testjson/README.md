编译连接指令：

```shell
g++ -std=c++17  main.cpp -o main  `pkg-config --cflags --libs jsoncpp`
g++ -std=c++17  newmain.cpp -o newmain  `pkg-config --cflags --libs jsoncpp`
```