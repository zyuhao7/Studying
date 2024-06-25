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

   day-2024-6-25
   
   检索
    mysql> select * from account;
      +----+--------+---------+
      | id | name   | balance |
      +----+--------+---------+
      |  1 | 张三   |     300 |
      |  2 | 李四   |     350 |
      |  3 | 王五   |     500 |
      |  7 | 赵六   |     100 |
      +----+--------+---------+
    
  检索不同的行
    mysql> select distinct id from account;
  distinct 关键字只返回不同的行.

  限制结果
   mysql> select id from account limit 3;
          +----+
          | id |
          +----+
          |  1 |
          |  2 |
          |  3 |
          +----+
   limit 3 指示 MySQL 返回不多于 3 行.

   mysql> select id from account limit 3,4;
          +----+
          | id |
          +----+
          |  4 |
          |  5 |
          |  6 |
          |  7 |
          +----+
    limit 3,4 指示 MySQL 返回从行 3 开始的 4 行.

   使用完全限定的表明
    mysql> select account.id from account;
    mysql> select account.id from test.account;

    排序数据
    
     mysql> select  id,name from account order by name;
            +----+--------+
            | id | name   |
            +----+--------+
            |  1 | 张三   |
            |  6 | 张帅   |
            |  2 | 李四   |
            |  3 | 王五   |
            |  4 | 田琪   |
            |  7 | 赵六   |
            |  5 | 赵柳   |
            +----+--------+

    按多个列排序
     mysql> select id,name from account order by name,id;

    指定排序方向
     mysql> select  id,name from account order by name desc;

     mysql> select id from account order by id desc limit 1;
              +----+
              | id |
              +----+
              |  7 |
              +----+
     使用 order by 和 limit 找到列id最大的值.

     
    



*/
```
