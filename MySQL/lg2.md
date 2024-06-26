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

  day-2024-6-26
    使用 where 子句
     mysql> select  id, name from account where id=7;
            +----+--------+
            | id | name   |
            +----+--------+
            |  7 | 赵六   |
            +----+--------+
     
    where子句的位置:
      在同时使用 order by 和 where 子句时, 应该让 order by 位于where之后,否则会产生错误.
    
    where 子句操作符
      检查单个值
       mysql> select id, name from account where name="张三";
              +----+--------+
              | id | name   |
              +----+--------+
              |  1 | 张三   |
              +----+--------+
       mysql> select id, name from account where id < 3;
              +----+--------+
              | id | name   |
              +----+--------+
              |  1 | 张三   |
              |  2 | 李四   |
              +----+--------+

       mysql> select id, name from account where id <= 3;
              +----+--------+
              | id | name   |
              +----+--------+
              |  1 | 张三   |
              |  2 | 李四   |
              |  3 | 王五   |
              +----+--------+

       不匹配检查
        mysql> select id, name from account where id <> 3; (<> 等于 != )
              +----+--------+
              | id | name   |
              +----+--------+
              |  1 | 张三   |
              |  2 | 李四   |
              |  4 | 田琪   |
              |  5 | 赵柳   |
              |  6 | 张帅   |
              |  7 | 赵六   |
              +----+--------+

      单引号用来限定字符串, 如果将值域串类型的列进行比较, 则需要限定引号。 用来与数值列进行比较的值不用引号.

      范围值检查
        mysql> select id,name from account where id  between 3 and 5;
              +----+--------+
              | id | name   |
              +----+--------+
              |  3 | 王五   |
              |  4 | 田琪   |
              |  5 | 赵柳   |
              +----+--------+
              
      空值检查
        mysql> select * from account where id is not NULL;

  */
```
