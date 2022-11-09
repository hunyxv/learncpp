# 测试使用 MySQL Community C/C++

## 安装

下载地址：<https://dev.mysql.com/downloads/connector/cpp/>

mac 安装在了 /usr/local/mysql-connector-c++-x.xx 目录下

mysqlx 使用文档：<https://dev.mysql.com/doc/x-devapi-userguide/en/preface.html>

## 编写 pkg-config

在 `/usr/local/lib/pkgconfig` 下添加 mysql-connector.pc。

```Plain Text
# mysql-connector.pc
prefix=/usr/local/mysql-connector-c++
exec_prefix=/usr/local/mysql-connector-c++
libdir=${exec_prefix}/lib64
includedir=${prefix}/include

Name: mysql-connector
Description: MySQL Connector/C++
Version: 8.0.31
Cflags: -I${includedir}
Libs: -L${libdir} -lmysqlcppconn8-static
```

## 依赖

- openssl（libcrypto、libssl）
- resolv

## 测试用到的sql命令

```sql
--  创建数据库
create database library;     
use library;
 
--  创建图书表
CREATE TABLE books (
    id INT NOT NULL AUTO_INCREMENT,
    title VARCHAR(1024) NOT NULL,
    author VARCHAR(1024) NOT NULL,
    price INT NOT NULL DEFAULT 0,
    quantity INT NOT NULL DEFAULT 1,
    PRIMARY KEY (id)
)DEFAULT CHARACTER SET=UTF8;
show tables;
-- drop table books;
-- truncate table books;

-- 向表格中插入内容
insert into books(title,author,price,quantity)
values("Linux多线程服务器编程","陈硕",50,1);

insert into books(title,author,price,quantity)
values("C++ primer 中文版","Lippman",60,1);

-- 查询表中内容
select * from books;
```

## 编译命令

```shell
g++ -std=c++11 main.cpp -o main `pkg-config --cflags --libs mysql-connector libcrypto libssl`  -lresolv
```

libresolv.so  <resolv.h>   提供使用因特网域名服务器和服务的接口
