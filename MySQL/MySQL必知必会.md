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

day-2024-6-28
    
      组合 where 子句
        AND 操作符
         mysql> select id, name from account where id = 5 and balance <= 300;
                +----+--------+
                | id | name   |
                +----+--------+
                |  5 | 赵柳   |
                +----+--------+

        OR 操作符
         mysql> select prod_name, prod_price from products where vend_id = 1002 or vend_id = 1003;
              +----------------+------------+
              | prod_name      | prod_price |
              +----------------+------------+
              | Detonator      |      13.00 |
              | Bird seed      |      10.00 |
              | Carrots        |       2.50 |
              | Fuses          |       3.42 |
              | Oil can        |       8.99 |
              | Safe           |      50.00 |
              | Sling          |       4.49 |
              | TNT (1 stick)  |       2.50 |
              | TNT (5 sticks) |      10.00 |
              +----------------+------------+

        计算次序
          mysql> select vend_id, prod_name, prod_price from products where
          vend_id = 1002 or vend_id = 1003 and prod_price >= 10;
              +---------+-----------+------------+
              | vend_id | prod_name | prod_price |
              +---------+-----------+------------+
              |    1003 | Detonator |      13.00 |
              |    1002 | Fuses     |       3.42 |
              |    1002 | Oil can   |       8.99 |
              |    1003 | Safe      |      50.00 |
              +---------+-----------+------------+

          mysql> select vend_id, prod_name, prod_price from products where
          (vend_id = 1002 or vend_id = 1003) and prod_price >= 10;

              +---------+----------------+------------+
              | vend_id | prod_name      | prod_price |
              +---------+----------------+------------+
              |    1003 | Detonator      |      13.00 |
              |    1003 | Bird seed      |      10.00 |
              |    1003 | Safe           |      50.00 |
              |    1003 | TNT (5 sticks) |      10.00 |
              +---------+----------------+------------+

        IN 操作符
          mysql> select vend_id, prod_name, prod_price from products where vend_id in (1002,1003) order by prod_name;
              +---------+----------------+------------+
              | vend_id | prod_name      | prod_price |
              +---------+----------------+------------+
              |    1003 | Bird seed      |      10.00 |
              |    1003 | Carrots        |       2.50 |
              |    1003 | Detonator      |      13.00 |
              |    1002 | Fuses          |       3.42 |
              |    1002 | Oil can        |       8.99 |
              |    1003 | Safe           |      50.00 |
              |    1003 | Sling          |       4.49 |
              |    1003 | TNT (1 stick)  |       2.50 |
              |    1003 | TNT (5 sticks) |      10.00 |
              +---------+----------------+------------+

        为什么要用 IN 呢 ？ 而不是用 OR
          1. 在使用长的合法选项清单时, IN 操作符的语法更清楚且直观.
          2. 在使用 IN 时, 计算的次序更容易管理.
          3. IN 操作符一般比 OR 操作符清单执行更快.
          4. IN 的最大优点是可以包含其他 select 语句, 使能动态建立where子句.

        NOT 操作符
          mysql>  select vend_id, prod_name, prod_price from products 
          where vend_id not in (1002,1003) order by prod_name;
              +---------+--------------+------------+
              | vend_id | prod_name    | prod_price |
              +---------+--------------+------------+
              |    1001 | .5 ton anvil |       5.99 |
              |    1001 | 1 ton anvil  |       9.99 |
              |    1001 | 2 ton anvil  |      14.99 |
              |    1005 | JetPack 1000 |      35.00 |
              |    1005 | JetPack 2000 |      55.00 |
              +---------+--------------+------------+

      MySQL 中的 NOT :
        MySQL 支持使用 NOT 对 IN、 BETWEEN 和 EXISTS 子句取反,这与多数其他
        DBMS 允许使用 NOT 对各种条件取反有很大的差别.
        
    
day-2024-6-30
       LIKE 操作符
        百分号(%) 通配符
          mysql> select prod_id, prod_name from products where
          prod_name like "jet%";

              +---------+--------------+
              | prod_id | prod_name    |
              +---------+--------------+
              | JP1000  | JetPack 1000 |
              | JP2000  | JetPack 2000 |
              +---------+--------------+
          % 告诉MySQL接受jet之后的任意字符, 不管它有多少字符.

          mysql> select prod_id, prod_name from products where
          prod_name like "%anvil%";

              +---------+--------------+
              | prod_id | prod_name    |
              +---------+--------------+
              | ANV01   | .5 ton anvil |
              | ANV02   | 1 ton anvil  |
              | ANV03   | 2 ton anvil  |
              +---------+--------------+

        下划线(_) 通配符
             
           mysql> select prod_id, prod_name from products where
           prod_name like "_ ton anvil";
        
            +---------+-------------+
            | prod_id | prod_name   |
            +---------+-------------+
            | ANV02   | 1 ton anvil |
            | ANV03   | 2 ton anvil |
            +---------+-------------+

        使用通配符的技巧
           1. 不要过度使用通配符.
           2. 在确实需要使用通配符时, 除非绝对有必要, 否则不要把它们
           用在搜索模式的开始处.
           3. 仔细注意通配符的位置.
      

        正则表达式
           具体学习看《正则表达式必知必会》

           使用 MySQL 正则表达式
             基本字符匹配

              mysql> select prod_name from products where prod_name 
              regexp "1000" order by prod_name;
              +--------------+
              | prod_name    |
              +--------------+
              | JetPack 1000 |
              +--------------+

              mysql> select prod_name from products where 
              prod_name regexp ".000" order by prod_name;
              +--------------+
              | prod_name    |
              +--------------+
              | JetPack 1000 |
              | JetPack 2000 |
              +--------------+

         进行 OR 匹配
              mysql> select prod_name from products where 
              prod_name regexp "1000|2000" order by prod_name;
              +--------------+
              | prod_name    |
              +--------------+
              | JetPack 1000 |
              | JetPack 2000 |
              +--------------+

         匹配几个字符之一
              mysql> select prod_name from products where 
              prod_name regexp "[123] Ton" order by prod_name;
              +-------------+
              | prod_name   |
              +-------------+
              | 1 ton anvil |
              | 2 ton anvil |
              +-------------+

              mysql> select prod_name from products where 
              prod_name regexp "1|2|3 Ton" order by prod_name;
              +---------------+
              | prod_name     |
              +---------------+
              | 1 ton anvil   |
              | 2 ton anvil   |
              | JetPack 1000  |
              | JetPack 2000  |
              | TNT (1 stick) |
              +---------------+
        字符集合也可以被否定, 即 他们将匹配除指定字符外的任何东西.
        为否定一个字符集, 在集合的开始处放置一个 ^ 即可.
        因此, 尽管 [123]匹配字符1、2或3, 但[^123] 却匹配除这些字符外的任何东西.

        匹配范围
              mysql> select prod_name from products where 
              prod_name regexp  "[1-5] Ton" order by prod_name;
              +--------------+
              | prod_name    |
              +--------------+
              | .5 ton anvil |
              | 1 ton anvil  |
              | 2 ton anvil  |
              +--------------+

        匹配特殊字符
              mysql> select vend_name from vendors where 
              vend_name regexp "." order by vend_name;
              +----------------+
              | vend_name      |
              +----------------+
              | ACME           |
              | Anvils R Us    |
              | Furball Inc.   |
              | Jet Set        |
              | Jouets Et Ours |
              | LT Supplies    |
              +----------------+

              mysql> select vend_name from vendors where
              vend_name regexp "\\." order by vend_name;
              +--------------+
              | vend_name    |
              +--------------+
              | Furball Inc. |
              +--------------+
day-2024-7-2
        匹配字符类
          [:alnum:] 任意字母和数字 (同[a-zA-Z0-9])
          [:alpha:] 任意字符(同[a-zA-Z])
          [:blank:] 空格和制表(同[\\t])
          [:cntrl:] ASCII控制字符(ASCII 0 到 31 和 127)
          [:digit:] 任意数字 (同[0-9])
          [:graph:] 和[:print:] 相同, 但不包括空格
          [:lower:] 任意小写字母
          [:print:] 任意可打印字符
          [:punct:] 既不在[:alnum:] 又不在[:cntrl:]中的任意字符.
          [:space:] 包括空格在内的任意空白字符
          [:upper:] 任意大写字母
          [:xdigit:] 任意十六进制数字 同[a-fA-F0-9]

        匹配多个实例
                        重复元字符
          *              0个或多个匹配
          +              1个或多个匹配(等于{1,})
          ?              0个或1个匹配(等于{0,1})
          {n}            指定数目的匹配
          {n,}           不少于指定数目的匹配
          {n,m}          匹配数目的范围(m 不超过 255)
      
      mysql> select prod_name from products where
              prod_name regexp "\\([0-9] sticks?\\)" order by
              prod_name;

            +----------------+
            | prod_name      |
            +----------------+
            | TNT (1 stick)  |
            | TNT (5 sticks) |
            +----------------+

      mysql> select prod_name from products where
             prod_name regexp "[[:digit:]]{4}" order by
             prod_name;

            +--------------+
            | prod_name    |
            +--------------+
            | JetPack 1000 |
            | JetPack 2000 |
            +--------------+    

        定位符

          ^           文本的开始
          $           文本的结尾
          [[:<:]]     词的开始
          [[:>:]]     词的结尾

      mysql> select prod_name from products where 
            prod_name regexp "^[0-9\\.]" order by prod_name;
            +--------------+
            | prod_name    |
            +--------------+
            | .5 ton anvil |
            | 1 ton anvil  |
            | 2 ton anvil  |
            +--------------+  
  */
```

```C++
    第10章 创建计算字段
       拼接字段

ps:
拼接: 将值联结到一起构成单个值.

      mysql> select Concat(vend_name,"(", vend_country, ")") 
        from vendors order by vend_name;

        +------------------------------------------+
        | Concat(vend_name,"(", vend_country, ")") |
        +------------------------------------------+
        | ACME(USA)                                |
        | Anvils R Us(USA)                         |
        | Furball Inc.(USA)                        |
        | Jet Set(England)                         |
        | Jouets Et Ours(France)                   |
        | LT Supplies(USA)                         |
        +------------------------------------------+

      mysql> select Concat(RTrim(vend_name), "(", vend_country, ")")
         from vendors order by vend_name;

        +--------------------------------------------------+
        | Concat(RTrim(vend_name), "(", vend_country, ")") |
        +--------------------------------------------------+
        | ACME(USA)                                        |
        | Anvils R Us(USA)                                 |
        | Furball Inc.(USA)                                |
        | Jet Set(England)                                 |
        | Jouets Et Ours(France)                           |
        | LT Supplies(USA)                                 |
        +--------------------------------------------------+  
// RTrim() 函数去掉值右边的所有空格.... 没看出来..

    使用别名
      mysql> select Concat(RTrim(vend_name), "(", RTrim(vend_country), ")") 
      as vend_title from vendors order by vend_name;

        +------------------------+
        | vend_title             |
        +------------------------+
        | ACME(USA)              |
        | Anvils R Us(USA)       |
        | Furball Inc.(USA)      |
        | Jet Set(England)       |
        | Jouets Et Ours(France) |
        | LT Supplies(USA)       |
        +------------------------+  

    执行算数计算
      mysql> select prod_id, quantity,order_num, item_price from orderitems where order_num = 20005;

        +---------+----------+-----------+------------+
        | prod_id | quantity | order_num | item_price |
        +---------+----------+-----------+------------+
        | ANV01   |       10 |     20005 |       5.99 |
        | ANV02   |        3 |     20005 |       9.99 |
        | TNT2    |        5 |     20005 |      10.00 |
        | FB      |        1 |     20005 |      10.00 |
        +---------+----------+-----------+------------+
       mysql> select prod_id, quantity, item_price, quantity * item_price 
         as expanded_price from orderitems where order_num = 20005;

        +---------+----------+------------+----------------+
        | prod_id | quantity | item_price | expanded_price |
        +---------+----------+------------+----------------+
        | ANV01   |       10 |       5.99 |          59.90 |
        | ANV02   |        3 |       9.99 |          29.97 |
        | TNT2    |        5 |      10.00 |          50.00 |
        | FB      |        1 |      10.00 |          10.00 |
        +---------+----------+------------+----------------+
// MySQL 算术运算符支持 + - * \ 运算. 
```

```c++
day-2024-7-4
   使用数据处理函数
   
       mysql> select vend_name, Upper(vend_name) as vend_name_upcase from vendors order by vend_name;
        +----------------+------------------+
        | vend_name      | vend_name_upcase |
        +----------------+------------------+
        | ACME           | ACME             |
        | Anvils R Us    | ANVILS R US      |
        | Furball Inc.   | FURBALL INC.     |
        | Jet Set        | JET SET          |
        | Jouets Et Ours | JOUETS ET OURS   |
        | LT Supplies    | LT SUPPLIES      |
        +----------------+------------------+

        常用的文本处理函数
      Left()          返回串左边的字符
      Length()        返回串的长度
      Locate()        找出串的一个子串
      Lower()         将串转换为小写
      LTrim()         去掉串左边的空格
      Right()         返回串右边的字符
      RTrim()         去掉串右边的空格
      Soundex()       返回串的 SOUNDEX 值
      SubString()     返回子串的字符
      Upper()         将串转换为大写

      mysql> select cust_name, cust_contact from customers where cust_contact="Y.Lie";
        Empty set (0.00 sec)

      mysql> select cust_name, cust_contact from customers where Soundex(cust_contact)=Soundex("Y.Lie");

        +-------------+--------------+
        | cust_name   | cust_contact |
        +-------------+--------------+
        | Coyote Inc. | Y Lee        |
        +-------------+--------------+

    日期和时间处理函数

        mysql> select cust_id, order_num,order_date from orders where order_date="2005-09-01";

        +---------+-----------+---------------------+
        | cust_id | order_num | order_date          |
        +---------+-----------+---------------------+
        |   10001 |     20005 | 2005-09-01 00:00:00 |
        +---------+-----------+---------------------+

        mysql> select cust_id, order_num,order_date from orders where Date(order_date)="2005-09-01";

        +---------+-----------+---------------------+
        | cust_id | order_num | order_date          |
        +---------+-----------+---------------------+
        |   10001 |     20005 | 2005-09-01 00:00:00 |
        +---------+-----------+---------------------+

        mysql> select cust_id, order_num from orders where Date(order_date) between "2005-09-01" and "2005-09-30";

        +---------+-----------+---------------------+
        | cust_id | order_num | order_date          |
        +---------+-----------+---------------------+
        |   10001 |     20005 | 2005-09-01 00:00:00 |
        |   10003 |     20006 | 2005-09-12 00:00:00 |
        |   10004 |     20007 | 2005-09-30 00:00:00 |
        +---------+-----------+---------------------+

        mysql> select cust_id, order_num,order_date  from orders where Year(order_date)=2005 and Month(order_date)=9;

        +---------+-----------+---------------------+
        | cust_id | order_num | order_date          |
        +---------+-----------+---------------------+
        |   10001 |     20005 | 2005-09-01 00:00:00 |
        |   10003 |     20006 | 2005-09-12 00:00:00 |
        |   10004 |     20007 | 2005-09-30 00:00:00 |
        +---------+-----------+---------------------+

    数值处理函数
              常用数值处理函数
            Abs()               返回一个数的绝对值
            Cos()               返回一个角度的余弦
            Exp()               返回一个数的指数值
            Mod()               返回除操作的余数
            Pi()                返回圆周率
            Rand()              返回一个随机数
            Sin()               返回一个角度的正弦
            Sqrt()              返回一个数的平凡根
            Tan()               返回一个角度的正切
            

```