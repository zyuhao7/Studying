## MySQL必知必会（文字版）

```c++
// day-2024-6-24
/*
      DBMS(数据库管理系统)
    
    创建数据库
     mysql> create database crashcourse;
     mysql> use crashcourse;

    显示数据库名
     mysql> show databases;

    显示数据库表信息
     mysql> show tables;

    显示表列信息
     mysql> show columns from account;
     +---------+-------------+------+-----+---------+----------------+
    | Field   | Type        | Null | Key | Default | Extra          |
    +---------+-------------+------+-----+---------+----------------+
    | id      | int(11)     | NO   | PRI | NULL    | auto_increment |
    | name    | varchar(30) | NO   |     |         |                |
    | balance | int(11)     | NO   |     | 0       |                |
    +---------+-------------+------+-----+---------+----------------+
    快捷方式:  mysql>  desc account;

    其他show语句还有:
     mysql> show status;     用于显示广泛的服务器状态信息
     mysql> show create database 和 show create table 用与现实创建特定数据库或表的MySQL语句
     mysql> show grants;  用于显示授予用户的安全权限
     mysql> show errors和 show warnings 用于显示服务器错误或警告信息


*/





```
