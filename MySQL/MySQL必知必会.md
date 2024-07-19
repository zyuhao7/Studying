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

```c++
day-2024-7-5

    汇总数据
      聚集函数
            SQL聚集函数
          AVG()                返回某列的平均值
          count()              返回某列的行数
          max()                返回某列的最大值
          min()                返回某列的最小值
          sum()                返回某列之和

     AVG() 函数
       mysql>  select avg(prod_price) as avg_price from products;
            +-----------+
            | avg_price |
            +-----------+
            | 16.133571 |
            +-----------+

       mysql> select vend_id, avg(prod_price) as avg_price from products where vend_id = 1003;
          +---------+-----------+
          | vend_id | avg_price |
          +---------+-----------+
          |    1003 | 13.212857 |
          +---------+-----------+

     count()函数 
       mysql> select count(*) as num_cust from customers;
          +----------+
          | num_cust |
          +----------+
          |        5 |
          +----------+
    
       mysql> select count(cust_email) as num_cust from customers;
          +----------+
          | num_cust |
          +----------+
          |        3 |
          +----------+

     max()函数
       mysql> select max(prod_price) as max_price from products;
          +-----------+
          | max_price |
          +-----------+
          |     55.00 |
          +-----------+
     
     min()函数
       mysql> select min(prod_price) as min_price from products;
          +-----------+
          | min_price |
          +-----------+
          |      2.50 |
          +-----------+

     sum()函数
       mysql> select  sum(quantity) as items_ordered from orderitems where order_num=20005;
          +---------------+
          | items_ordered |
          +---------------+
          |            19 |
          +---------------+ 

       mysql> select sum(item_price * quantity) as total_price from orderitems where order_num=20005;
          +-------------+
          | total_price |
          +-------------+
          |      149.87 |
          +-------------+
       
      聚集不同的值
       mysql>  select avg(distinct prod_price) as avg_price from products where vend_id = 1003;
          +-----------+
          | avg_price |
          +-----------+
          | 15.998000 |
          +-----------+
          使用 distinct参数, 平均值只考虑不同的价格.

    组合聚集函数
       mysql> select count(*) as num_items, min(prod_price) 
                              as price_min, max(prod_price) 
                              as price_max, avg(prod_price) 
                              as price_avg from products;

          +-----------+-----------+-----------+-----------+
          | num_items | price_min | price_max | price_avg |
          +-----------+-----------+-----------+-----------+
          |        14 |      2.50 |     55.00 | 16.133571 |
          +-----------+-----------+-----------+-----------+ 
```

```c++
day-2024-7-7
    分组数据
      数据分组
        mysql> select count(*) as num_prods from products where vend_id = 1003;
          +-----------+
          | num_prods |
          +-----------+
          |         7 |
          +-----------+

      创建分组
        mysql> select vend_id, count(*) as num_prods from products group by vend_id;
          +---------+-----------+
          | vend_id | num_prods |
          +---------+-----------+
          |    1001 |         3 |
          |    1002 |         2 |
          |    1003 |         7 |
          |    1005 |         2 |
          +---------+-----------+
//ps: 使用 rollup  使用 with rollup 关键字, 可以得到每个分组以及每个分组汇总级别的值:

        mysql> select vend_id, count(*) as num_prods from products group by vend_id with rollup;
          +---------+-----------+
          | vend_id | num_prods |
          +---------+-----------+
          |    1001 |         3 |
          |    1002 |         2 |
          |    1003 |         7 |
          |    1005 |         2 |
          |    NULL |        14 |
          +---------+-----------+

    过滤分组
// ps: having 非常类似 where. In fact, 目前为止学过的所有类型的 where 子句都可以用 having 来替代. 唯一的差别是 where 过滤 行, 而 having 过滤 分组.

      mysql> select cust_id, count(*) as orders from orders group by cust_id having count(*) >= 2;
          +---------+--------+
          | cust_id | orders |
          +---------+--------+
          |   10001 |      2 |
          +---------+--------+
// ps: having 和where 的差别 : where在数据分组前进行过滤, having 在数据分组后进行过滤. where 排除的行不包括在分组中. 这可能会改变计算值, 从而影响 having 子句中基于这些值过滤掉的分组.

      mysql> select vend_id, count(*) as num_prodsfrom products
             where prod_price >= 10 group by vend_id
             having  count(*) >= 2;
          +---------+-----------+
          | vend_id | num_prods |
          +---------+-----------+
          |    1003 |         4 |
          |    1005 |         2 |
          +---------+-----------+

      //(没有 where 子句)
      mysql> select vend_id, count(*) as num_prods from products group by vend_id having count(*) >= 2;                   
          +---------+-----------+
          | vend_id | num_prods |
          +---------+-----------+
          |    1001 |         3 |
          |    1002 |         2 |
          |    1003 |         7 |
          |    1005 |         2 |
          +---------+-----------+
    
    分组和排序
                    order by 和 group by
        order by                          group by
     排序产生的输出                 分组行. 但输出可能不是分组的顺序.
    任意列都可以使用      只能使用选择列或表达式列, 而且必须使用每个选择列表达式
       不一定需要                 如果与聚集函数一起使用列,则必须使用

  
      mysql> select order_num, sum(quantity * item_price) as ordertotal from orderitems group by order_num having sum(quantity * item_price) >= 50;
          +-----------+------------+
          | order_num | ordertotal |
          +-----------+------------+
          |     20005 |     149.87 |
          |     20006 |      55.00 |
          |     20007 |    1000.00 |
          |     20008 |     125.00 |
          +-----------+------------+

      mysql> select order_num, sum(quantity * item_price) as ordertotal from orderitemsgroup by order_num having sum(quantity * item_price)>=50 order by ordertotal;
          +-----------+----------------+
          | order_num | orderitemtotal |
          +-----------+----------------+
          |     20006 |          55.00 |
          |     20008 |         125.00 |
          |     20005 |         149.87 |
          |     20007 |        1000.00 |
          +-----------+----------------+

    select子句顺序
                        select子句及其顺序

          子句                说明                  是否必须使用
        select         要返回的列或表达式                 是
        from           从中检索数据的表           仅在表选择数据时使用
        where          行级过滤                           否
        group by       分组说明                    仅在按组计算聚集时使用
        having         组级过滤                           否
        order by       输出排列顺序                       否
        limit          检索的行数                         否

```

```c++
  day-2024-7-8
      使用子查询
        利用子查询进行过滤
        mysql> select order_num from orderitems where prod_Id = "TNT2";
          +-----------+
          | order_num |
          +-----------+
          |     20005 |
          |     20007 |
          +-----------+
        
        mysql> select cust_id from orders where order_num in (20005,20007);
          +---------+
          | cust_id |
          +---------+
          |   10001 |
          |   10004 |
          +---------+

      mysql> select cust_id from orders where order_num in (select order_num from orderitems where prod_id="TNT2");
          +---------+
          | cust_id |
          +---------+
          |   10001 |
          |   10004 |
          +---------+
      
      mysql> select cust_name, cust_contact from customers where cust_id in(10001,10004);
          +----------------+--------------+
          | cust_name      | cust_contact |
          +----------------+--------------+
          | Coyote Inc.    | Y Lee        |
          | Yosemite Place | Y Sam        |
          +----------------+--------------+
```
```c++

 day-2024-7-8

   使用子查询

​    利用子查询进行过滤

​    mysql> select order_num from orderitems where prod_Id = "TNT2";

​     +-----------+
​     | order_num |
​     +-----------+
​     |   20005   |
​     |   20007   |
​     +-----------+

​    mysql> select cust_id from orders where order_num in (20005,20007);

​     +---------+
​     | cust_id |
​     +---------+
​     |  10001  |
​     |  10004  |
​     +---------+



   mysql> select cust_id from orders where order_num in (select order_num from orderitems where prod_id="TNT2");

​     +---------+
​     | cust_id |
​     +---------+
​     |  10001  |
​     |  10004  |
​     +---------+

   mysql> select cust_name, cust_contact from customers where cust_id in(10001,10004);

​     +----------------+--------------+
​     | cust_name    | cust_contact   |
​     +----------------+--------------+
​     | Coyote Inc.   | Y Lee         |
​     | Yosemite Place | Y Sam        |
​     +----------------+--------------+

   mysql> select cust_name, cust_contact from customers where cust_id 
   in (select cust_id from orders where order_num in 
   (select order_num from orderitems where prod_id = "TNT2"));

​     +----------------+--------------+
​     | cust_name    | cust_contact   |
​     +----------------+--------------+
​     | Coyote Inc.   | Y Lee         |
​     | Yosemite Place | Y Sam        |
​     +----------------+--------------+

    mysql> select cust_name, cust_state,(select count(*) from orders where orders.cust_id=customers.cust_id) as
     orders from customers order by cust_name;

        +----------------+------------+--------+
        | cust_name      | cust_state | orders |
        +----------------+------------+--------+
        | Coyote Inc.    | MI         |      2 |
        | E Fudd         | IL         |      1 |
        | Mouse House    | OH         |      0 |
        | Wascals        | IN         |      1 |
        | Yosemite Place | AZ         |      1 |
        +----------------+------------+--------+
​
mysql> select cust_name, cust_state, (select count(*) from orders where cust_id = cust_id) as orders
     from customers order by cust_name;
    
        +----------------+------------+--------+
        | cust_name      | cust_state | orders |
        +----------------+------------+--------+
        | Coyote Inc.    | MI         |      5 |
        | E Fudd         | IL         |      5 |
        | Mouse House    | OH         |      5 |
        | Wascals        | IN         |      5 |
        | Yosemite Place | AZ         |      5 |
        +----------------+------------+--------+

```

```c++
day-7-9
    联结表
    联结:  SQL 最强大的功能之一就是能在数据检索查询的执行中联结(join)表.
    联结是利用 SQL 的 select 能执行的最重要的操作, 很好地理解联结及其语法是学习 SQL 重要组成部分.

    1. 关系表
Ps: 外键
      外键为某个表中的一列, 它包含另一个表的主键值, 定义了两个表之间的关系.
    
    2. 创建联结
      mysql> select vend_name, prod_name, prod_price from
        vendors, products where vendors.vend_id = products.vend_id
        order by vend_name, prod_name;
          +-------------+----------------+------------+
          | vend_name   | prod_name      | prod_price |
          +-------------+----------------+------------+
          | ACME        | Bird seed      |      10.00 |
          | ACME        | Carrots        |       2.50 |
          | ACME        | Detonator      |      13.00 |
          | ACME        | Safe           |      50.00 |
          | ACME        | Sling          |       4.49 |
          | ACME        | TNT (1 stick)  |       2.50 |
          | ACME        | TNT (5 sticks) |      10.00 |
          | Anvils R Us | .5 ton anvil   |       5.99 |
          | Anvils R Us | 1 ton anvil    |       9.99 |
          | Anvils R Us | 2 ton anvil    |      14.99 |
          | Jet Set     | JetPack 1000   |      35.00 |
          | Jet Set     | JetPack 2000   |      55.00 |
          | LT Supplies | Fuses          |       3.42 |
          | LT Supplies | Oil can        |       8.99 |
          +-------------+----------------+------------+
Ps: 笛卡尔积
      由没有联结条件的表关系返回的结果为笛卡尔积. 检索出来的行的数目将是第一个表中的行数乘以第二个表中的行数.

      mysql> select vend_name, prod_name, prod_price from vendors, products order by vend_name, prod_name;
          +----------------+----------------+------------+
          | vend_name      | prod_name      | prod_price |
          +----------------+----------------+------------+
          | ACME           | .5 ton anvil   |       5.99 |
          | ACME           | 1 ton anvil    |       9.99 |
          | ACME           | 2 ton anvil    |      14.99 |
          | ACME           | Bird seed      |      10.00 |
          | ACME           | Carrots        |       2.50 |
          | ACME           | Detonator      |      13.00 |
          | ACME           | Fuses          |       3.42 |
          | ACME           | JetPack 1000   |      35.00 |
          | ACME           | JetPack 2000   |      55.00 |
          | ACME           | Oil can        |       8.99 |
          | ACME           | Safe           |      50.00 |
                  ........ 略.......

      2.2 内部联结
        mysql> select vend_name, prod_name from vendors inner join products on vendors.vend_id=products.vend_id;
          +-------------+----------------+
          | vend_name   | prod_name      |
          +-------------+----------------+
          | Anvils R Us | .5 ton anvil   |
          | Anvils R Us | 1 ton anvil    |
          | Anvils R Us | 2 ton anvil    |
          | LT Supplies | Fuses          |
          | LT Supplies | Oil can        |
          | ACME        | Detonator      |
          | ACME        | Bird seed      |
          | ACME        | Carrots        |
          | ACME        | Safe           |
          | ACME        | Sling          |
          | ACME        | TNT (1 stick)  |
          | ACME        | TNT (5 sticks) |
          | Jet Set     | JetPack 1000   |
          | Jet Set     | JetPack 2000   |
          +-------------+----------------+
        
      2.3联结多个表
         mysql> select prod_name, vend_name, prod_price, quantity from orderitems, products, vendors
          where products.vend_id=vendors.vend_id and orderitems.prod_id=products.prod_id and order_num=20005;
          +----------------+-------------+------------+----------+-----------+
          | prod_name      | vend_name   | prod_price | quantity | order_num |
          +----------------+-------------+------------+----------+-----------+
          | .5 ton anvil   | Anvils R Us |       5.99 |       10 |     20005 |
          | 1 ton anvil    | Anvils R Us |       9.99 |        3 |     20005 |
          | TNT (5 sticks) | ACME        |      10.00 |        5 |     20005 |
          | Bird seed      | ACME        |      10.00 |        1 |     20005 |
          +----------------+-------------+------------+----------+-----------+
``` 

```c++
day-2024-7-10
      创建高级联结
        1. 使用表别名 
        mysql> select Concat(RTrim(vend_name), "(", RTrim(vend_country), ")") as vend_titile from vendors
        order by vend_name;
          +------------------------+
          | vend_titile            |
          +------------------------+
          | ACME(USA)              |
          | Anvils R Us(USA)       |
          | Furball Inc.(USA)      |
          | Jet Set(England)       |
          | Jouets Et Ours(France) |
          | LT Supplies(USA)       |
          +------------------------+
       
        2. 使用不同类型的联结

          2.1 自联结
          mysql> select prod_id, prod_name from products where 
          vend_id= (select vend_id from products where prod_id="DTNTR");
          +---------+----------------+
          | prod_id | prod_name      |
          +---------+----------------+
          | DTNTR   | Detonator      |
          | FB      | Bird seed      |
          | FC      | Carrots        |
          | SAFE    | Safe           |
          | SLING   | Sling          |
          | TNT1    | TNT (1 stick)  |
          | TNT2    | TNT (5 sticks) |
          +---------+----------------+

          mysql> select p1.prod_id, p1.prod_name from products as p1, 
          products as p2 where p1.vend_id=p2.vend_id and p2.prod_id="DTNTR";
          +---------+----------------+
          | prod_id | prod_name      |
          +---------+----------------+
          | DTNTR   | Detonator      |
          | FB      | Bird seed      |
          | FC      | Carrots        |
          | SAFE    | Safe           |
          | SLING   | Sling          |
          | TNT1    | TNT (1 stick)  |
          | TNT2    | TNT (5 sticks) |
          +---------+----------------+

         2.2 自然联结
          mysql> select c.*, o.order_num, o.order_date,
                oi.prod_id, oi.quantity, OI.item_price
                from customers as c, orders as o, orderitems as oi
                where c.cust_id=o.cust_id
                and oi.order_num=o.order_num
                and prod_id="FB";
+---------+-------------+----------------+-----------+------------+----------+--------------+--------------+-----------------+-----------+---------------------+---------+----------+------------+
| cust_id | cust_name   | cust_address   | cust_city | cust_state | cust_zip | cust_country | cust_contact | cust_email      | order_num | order_date          | prod_id | quantity | item_price |
+---------+-------------+----------------+-----------+------------+----------+--------------+--------------+-----------------+-----------+---------------------+---------+----------+------------+
|   10001 | Coyote Inc. | 200 Maple Lane | Detroit   | MI         | 44444    | USA          | Y Lee        | ylee@coyote.com |     20005 | 2005-09-01 00:00:00 | FB      |        1 |      10.00 |
|   10001 | Coyote Inc. | 200 Maple Lane | Detroit   | MI         | 44444    | USA          | Y Lee        | ylee@coyote.com |     20009 | 2005-10-08 00:00:00 | FB      |        1 |      10.00 |
+---------+-------------+----------------+-----------+------------+----------+--------------+--------------+-----------------+-----------+---------------------+---------+----------+------------+

        2.3 外部联结
          mysql> select customers.cust_id, orders.order_num from
          customers inner join orders on customers.cust_id=orders.cust_id;
          +---------+-----------+
          | cust_id | order_num |
          +---------+-----------+
          |   10001 |     20005 |
          |   10001 |     20009 |
          |   10003 |     20006 |
          |   10004 |     20007 |
          |   10005 |     20008 |
          +---------+-----------+

          mysql> select customers.cust_id, orders.order_num from
          customers left outer join orders on customers.cust_id=orders.cust_id;
          +---------+-----------+
          | cust_id | order_num |
          +---------+-----------+
          |   10001 |     20005 |
          |   10001 |     20009 |
          |   10002 |      NULL |
          |   10003 |     20006 |
          |   10004 |     20007 |
          |   10005 |     20008 |
          +---------+-----------+

      3. 使用带聚集函数的联结
        mysql> select customers.cust_name, customers.cust_id,
        count(orders.order_num) as num_ord from customers inner join
        orders on customers.cust_id=orders.cust_id group by customers.cust_id;
        +----------------+---------+---------+
        | cust_name      | cust_id | num_ord |
        +----------------+---------+---------+
        | Coyote Inc.    |   10001 |       2 |
        | Wascals        |   10003 |       1 |
        | Yosemite Place |   10004 |       1 |
        | E Fudd         |   10005 |       1 |
        +----------------+---------+---------+

        mysql> select customers.cust_name, customers.cust_id,
        count (orders.order_num) as num_ord from customers 
        left outer join orders on customers.cust_id=orders.cust_id 
        group by customers.cust_id;   
          +----------------+---------+---------+
          | cust_name      | cust_id | num_ord |
          +----------------+---------+---------+
          | Coyote Inc.    |   10001 |       2 |
          | Mouse House    |   10002 |       0 |
          | Wascals        |   10003 |       1 |
          | Yosemite Place |   10004 |       1 |
          | E Fudd         |   10005 |       1 |
          +----------------+---------+---------+
      
      4. 使用联结和联结条件
        
```

```c++
// day-2024-7-11
      组合查询

       1.创建组合查询
        1.1 使用 union
          mysql> select vend_id, prod_id, prod_price from products where prod_price<=5;
          +---------+---------+------------+
          | vend_id | prod_id | prod_price |
          +---------+---------+------------+
          |    1003 | FC      |       2.50 |
          |    1002 | FU1     |       3.42 |
          |    1003 | SLING   |       4.49 |
          |    1003 | TNT1    |       2.50 |
          +---------+---------+------------+

         mysql> select vend_id, prod_id, prod_price from products where vend_id in(1001,1002);
          +---------+---------+------------+
          | vend_id | prod_id | prod_price |
          +---------+---------+------------+
          |    1001 | ANV01   |       5.99 |
          |    1001 | ANV02   |       9.99 |
          |    1001 | ANV03   |      14.99 |
          |    1002 | FU1     |       3.42 |
          |    1002 | OL1     |       8.99 |
          +---------+---------+------------+

        mysql> select vend_id,prod_id,prod_price from products
           where prod_price<=5 union select vend_id,prod_id,prod_price
           from products where vend_id in (1001,1002);
          +---------+---------+------------+
          | vend_id | prod_id | prod_price |
          +---------+---------+------------+
          |    1003 | FC      |       2.50 |
          |    1002 | FU1     |       3.42 |
          |    1003 | SLING   |       4.49 |
          |    1003 | TNT1    |       2.50 |
          |    1001 | ANV01   |       5.99 |
          |    1001 | ANV02   |       9.99 |
          |    1001 | ANV03   |      14.99 |
          |    1002 | OL1     |       8.99 |
          +---------+---------+------------+
        
        mysql> select vend_id,prod_id,prod_price from products
               where prod_price<=5 or vend_id in (1001,1002);
          +---------+---------+------------+
          | vend_id | prod_id | prod_price |
          +---------+---------+------------+
          |    1001 | ANV01   |       5.99 |
          |    1001 | ANV02   |       9.99 |
          |    1001 | ANV03   |      14.99 |
          |    1003 | FC      |       2.50 |
          |    1002 | FU1     |       3.42 |
          |    1002 | OL1     |       8.99 |
          |    1003 | SLING   |       4.49 |
          |    1003 | TNT1    |       2.50 |
          +---------+---------+------------+
        
      1.2 union 规则
          1. union 必须由两条或多条select语句组成, 语句之间用 union 分隔.
          2. union 中的每个查询必须包含相同的列、  表达式或聚集函数.
          3. 列数据类型必须兼容, 类型不必完全相同, 但必须是 DBMS 可以隐含低转换的类型.

      1.3 包含或取消重复的行

         mysql> select vend_id, prod_id, prod_price from products
          where prod_price<=5 union all select vend_id, prod_id,
          prod_pricefrom products where vend_id in(1001,1002);
          +---------+---------+------------+
          | vend_id | prod_id | prod_price |
          +---------+---------+------------+
          |    1003 | FC      |       2.50 |
          |    1002 | FU1     |       3.42 |
          |    1003 | SLING   |       4.49 |
          |    1003 | TNT1    |       2.50 |
          |    1001 | ANV01   |       5.99 |
          |    1001 | ANV02   |       9.99 |
          |    1001 | ANV03   |      14.99 |
          |    1002 | FU1     |       3.42 |
          |    1002 | OL1     |       8.99 |
          +---------+---------+------------+

      1.4 对组合查询结果排序
        mysql> select vend_id, prod_id, prod_price from products
              where prod_price<=5 union select vend_id, prod_id,
              prod_price from products where vend_id in(1001,1002)
              order by vend_id, prod_price;
          +---------+---------+------------+
          | vend_id | prod_id | prod_price |
          +---------+---------+------------+
          |    1001 | ANV01   |       5.99 |
          |    1001 | ANV02   |       9.99 |
          |    1001 | ANV03   |      14.99 |
          |    1002 | FU1     |       3.42 |
          |    1002 | OL1     |       8.99 |
          |    1003 | FC      |       2.50 |
          |    1003 | TNT1    |       2.50 |
          |    1003 | SLING   |       4.49 |
          +---------+---------+------------+
```

```c++
day-7-13
    全文本搜索

      1. 使用全文本搜索
         启用全文本搜索

         mysql> create table productnotes(
             note_id int not null auto_increment,
             prod_id char(10) not null,
             note_date datetime not null,
             note_text text null,
             primary key(note_id),
             fulltext(note_text)) engine=MyISAM;
         
         进行全文本搜索
      在索引之后, 使用两个函数 Match() 和 Against() 执行全本文搜索,其中Match()指定被搜索的列,
      Against() 指定要使用的搜索表达式.

      mysql> select note_text from productnotes where match(note_text) against("rabbit");
          +----------------------------------------------------------------------------------------------------------------------+
          | note_text                                                                                                            |
          +----------------------------------------------------------------------------------------------------------------------+
          | Customer complaint: rabbit has been able to detect trap, food apparently less effective now.                         |
          | Quantity varies, sold by the sack load.
          All guaranteed to be bright and orange, and suitable for use as rabbit bait. |
          +----------------------------------------------------------------------------------------------------------------------+

      mysql> select note_text from productnotes where note_text like "%rabbit%";
          +----------------------------------------------------------------------------------------------------------------------+
          | note_text                                                                                                            |
          +----------------------------------------------------------------------------------------------------------------------+
          | Quantity varies, sold by the sack load.
          All guaranteed to be bright and orange, and suitable for use as rabbit bait. |
          | Customer complaint: rabbit has been able to detect trap, food apparently less effective now.                         |
          +----------------------------------------------------------------------------------------------------------------------+

      mysql> select note_text, match(note_text) against("rabbit") as rank from productnotes;
          +-----------------------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
          | note_text                                                                                                                                                 | rank               |
          +-----------------------------------------------------------------------------------------------------------------------------------------------------------+--------------------+
          | Customer complaint:
          Sticks not individually wrapped, too easy to mistakenly detonate all at once.
          Recommend individual wrapping.                          |                  0 |
          | Can shipped full, refills not available.
          Need to order new can if refill needed.                                                                          |                  0 |
          | Safe is combination locked, combination not provided with safe.
          This is rarely a problem as safes are typically blown up or dropped by customers.         |                  0 |
          | Quantity varies, sold by the sack load.
          All guaranteed to be bright and orange, and suitable for use as rabbit bait.                                      | 1.5905543565750122 |
          | Included fuses are short and have been known to detonate too quickly for some customers.
          Longer fuses are available (item FU1) and should be recommended. |                  0 |
          | Matches not included, recommend purchase of matches or detonator (item DTNTR).                                                                            |                  0 |
          | Please note that no returns will be accepted if safe opened using explosives.                                                                             |                  0 |
          | Multiple customer returns, anvils failing to drop fast enough or falling backwards on purchaser. Recommend that customer considers using heavier anvils.  |                  0 |
          | Item is extremely heavy. Designed for dropping, not recommended for use with slings, ropes, pulleys, or tightropes.                                       |                  0 |
          | Customer complaint: rabbit has been able to detect trap, food apparently less effective now.                                                              | 1.6408053636550903 |
          | Shipped unassembled, requires common tools (including oversized hammer).                                                                                  |                  0 |
          | Customer complaint:
          Circular hole in safe floor can apparently be easily cut with handsaw.                                                                |                  0 |
          | Customer complaint:
          Not heavy enough to generate flying stars around head of victim. If being purchased for dropping, recommend ANV02 or ANV03 instead.   |                  0 |
          | Call from individual trapped in safe plummeting to the ground, suggests an escape hatch be added.
          Comment forwarded to vendor.                            |                  0 |
          +-----------------------------------------------------------------------------------------------------------------------------------------------------------+--------------------+

         使用查询扩展

          mysql> select note_text from productnotes  where match  (note_text) against("anvils");
          +----------------------------------------------------------------------------------------------------------------------------------------------------------+
          | note_text                                                                                                                                                |
          +----------------------------------------------------------------------------------------------------------------------------------------------------------+
          | Multiple customer returns, anvils failing to drop fast enough or falling backwards on purchaser. Recommend that customer considers using heavier anvils. |
          +----------------------------------------------------------------------------------------------------------------------------------------------------------+

          mysql> select note_text from productnotes where match(note_text) against("anvils" with query expansion);
          +----------------------------------------------------------------------------------------------------------------------------------------------------------+
          | note_text                                                                                                                                                |
          +----------------------------------------------------------------------------------------------------------------------------------------------------------+
          | Multiple customer returns, anvils failing to drop fast enough or falling backwards on purchaser. Recommend that customer considers using heavier anvils. |
          | Customer complaint:
          Sticks not individually wrapped, too easy to mistakenly detonate all at once.
          Recommend individual wrapping.                         |
          | Customer complaint:
          Not heavy enough to generate flying stars around head of victim. If being purchased for dropping, recommend ANV02 or ANV03 instead.  |
          | Please note that no returns will be accepted if safe opened using explosives.                                                                            |
          | Customer complaint: rabbit has been able to detect trap, food apparently less effective now.                                                             |
          | Customer complaint:
          Circular hole in safe floor can apparently be easily cut with handsaw.                                                               |
          | Matches not included, recommend purchase of matches or detonator (item DTNTR).                                                                           |
          +----------------------------------------------------------------------------------------------------------------------------------------------------------+

         布尔文本搜索
          
          mysql> select note_text from productnotes where match(note_text) against("heavy" in boolean mode);
          +---------------------------------------------------------------------------------------------------------------------------------------------------------+
          | note_text                                                                                                                                               |
          +---------------------------------------------------------------------------------------------------------------------------------------------------------+
          | Item is extremely heavy. Designed for dropping, not recommended for use with slings, ropes, pulleys, or tightropes.                                     |
          | Customer complaint:
          Not heavy enough to generate flying stars around head of victim. If being purchased for dropping, recommend ANV02 or ANV03 instead. |
          +---------------------------------------------------------------------------------------------------------------------------------------------------------+

         mysql> select note_text from productnotes where match(note_text) against("heavy -rope*" in boolean mode); // 搜索不包含任意以 repo 开始的词的行.
          +---------------------------------------------------------------------------------------------------------------------------------------------------------+
          | note_text                                                                                                                                               |
          +---------------------------------------------------------------------------------------------------------------------------------------------------------+
          | Customer complaint:
          Not heavy enough to generate flying stars around head of victim. If being purchased for dropping, recommend ANV02 or ANV03 instead. |
          +---------------------------------------------------------------------------------------------------------------------------------------------------------+

                                                      全文本布尔操作符
                              布尔操作符                                            说明
                                  +                                            包含, 词必须存在
                                  -                                            排除, 词必须不出现
                                  >                                            包含, 而且增加等级值
                                  <                                            包含, 而且减少等级值
                                  ()                                           把词组成子表达式
                                  ~                                            取消一个词的排序值
                                  *                                            词尾的通配符
                                  ""                                           定义一个短句 
        
        // 匹配包含 rabbit 和 bait 的行.
        mysql> select note_text from productnotes where match(note_text) against("+rabbit +bait" in boolean mode);
          +----------------------------------------------------------------------------------------------------------------------+
          | note_text                                                                                                            |
          +----------------------------------------------------------------------------------------------------------------------+
          | Quantity varies, sold by the sack load.
          All guaranteed to be bright and orange, and suitable for use as rabbit bait. |
          +----------------------------------------------------------------------------------------------------------------------+
        
        // 匹配 rabbit 和 bait 至少一个词.
        mysql> select note_text from productnotes where match(note_text) against("rabbit bait" in boolean mode);
          +----------------------------------------------------------------------------------------------------------------------+
          | note_text                                                                                                            |
          +----------------------------------------------------------------------------------------------------------------------+
          | Quantity varies, sold by the sack load.
          All guaranteed to be bright and orange, and suitable for use as rabbit bait. |
          | Customer complaint: rabbit has been able to detect trap, food apparently less effective now.                         |
          +----------------------------------------------------------------------------------------------------------------------+

        //匹配短句 rabit bait 而不是匹配两个词 rabbit 和 bait.
        mysql> select note_text from productnotes where match(note_text) against('"rabbit bait"' in boolean mode);
          +----------------------------------------------------------------------------------------------------------------------+
          | note_text                                                                                                            |
          +----------------------------------------------------------------------------------------------------------------------+
          | Quantity varies, sold by the sack load.
          All guaranteed to be bright and orange, and suitable for use as rabbit bait. |
          +----------------------------------------------------------------------------------------------------------------------+

        //匹配 rabbit 和  carrot, 增加前者等级, 降低后者等级.
        mysql> select note_text from productnotes where match(note_text) against(">rabbit <carrot" in boolean mode);
          +----------------------------------------------------------------------------------------------------------------------+
          | note_text                                                                                                            |
          +----------------------------------------------------------------------------------------------------------------------+
          | Quantity varies, sold by the sack load.
          All guaranteed to be bright and orange, and suitable for use as rabbit bait. |
          | Customer complaint: rabbit has been able to detect trap, food apparently less effective now.                         |
          +----------------------------------------------------------------------------------------------------------------------+

        //匹配搜索词 safe 和 combination, 降低后者等级.
        mysql> select note_text from productnotes where match(note_text) against("+safe +(<combination)" in boolean mode);
          +---------------------------------------------------------------------------------------------------------------------------------------------------+
          | note_text                                                                                                                                         |
          +---------------------------------------------------------------------------------------------------------------------------------------------------+
          | Safe is combination locked, combination not provided with safe.
          This is rarely a problem as safes are typically blown up or dropped by customers. |
          +---------------------------------------------------------------------------------------------------------------------------------------------------+
```

```c++
day-2024-7-14
        插入数据
           插入完整的行

         mysql> insert into Customers values(NULL, "Pep E. LaPew", "100 Main Street", "Los Angels", "CA", "90046", "USA", NULL, NULL);
         Query OK, 1 row affected (0.04 sec)

           插入多个行

         mysql> insert into Customers values(NULL, "Pep E. LaPew", "100 Main Street", "Los Angels", "CA", "90046", "USA", NULL, NULL),
          (NULL, "Pep E.", "100 Main Street", "Los Angels", "CA", "90046", "USA", NULL, NULL);

           插入检索出来的数据 (列对应, 不关心名字是否一致)
        
         mysql> insert into customers(cust_id,
               cust_email,
               cust_name,
               cust_address,
               cust_city,
               cust_state,
               cust_zip,
               cust_country)
               select cust_id,
               cust_contact,
               cust_name,
               cust_address,
               cust_city,
               cust_state,
               cust_zip,
               cust_country from custnew;
```

```c++
day2024-7-15

        更新和删除数据

         更新数据

          mysql> update customers set cust_email="elmer@fudd.com" where cust_id=10005;
          Query OK, 1 row affected (0.03 sec)
          Rows matched: 1  Changed: 1  Warnings: 0

        // 更新多列
          mysql> update customers set cust_name="The Fudds", cust_email="elmer@Fudd.com" where cust_id=10005;
          Query OK, 1 row affected (0.01 sec)
          Rows matched: 1  Changed: 1  Warnings: 0        

          mysql> update customers set cust_email=NULL where cust_id=10005;
          Query OK, 1 row affected (0.03 sec)
          Rows matched: 1  Changed: 1  Warnings: 0

         删除数据
          
          mysql> delete from customers where  cust_id=10006;
          Query OK, 1 row affected (0.03 sec)

          //更快地删除方式, truncate, 实际上是删除原来的表重新再创建一个表, 而不是逐行删除表中的数据.
        
         更新和删除的指导原则
```

```c++
day-2024-7-15
        创建和操纵表

          1. 创建表
           mysql> create table ace( ace_num int not null auto_increment, ace_date datetime not null, ace_id int not null, primary key(ace_num)) engine=InnoDB;
           Query OK, 0 rows affected (0.05 sec)

          +----------+----------+------+-----+---------+----------------+
          | Field    | Type     | Null | Key | Default | Extra          |
          +----------+----------+------+-----+---------+----------------+
          | ace_num  | int(11)  | NO   | PRI | NULL    | auto_increment |
          | ace_date | datetime | NO   |     | NULL    |                |
          | ace_id   | int(11)  | NO   |     | NULL    |                |
          +----------+----------+------+-----+---------+----------------+

          2. 主键再介绍
           mysql> create table aceitems( ace_num int not null, ace_item int not null, ace_id char(10) not null, ace_name char(20) not null, ace_age int not null, primary key(ace_num, ace_item)) engine=InnoDB;
           Query OK, 0 rows affected (0.05 sec)

          +----------+----------+------+-----+---------+-------+
          | Field    | Type     | Null | Key | Default | Extra |
          +----------+----------+------+-----+---------+-------+
          | ace_num  | int(11)  | NO   | PRI | NULL    |       |
          | ace_item | int(11)  | NO   | PRI | NULL    |       |
          | ace_id   | char(10) | NO   |     | NULL    |       |
          | ace_name | char(20) | NO   |     | NULL    |       |
          | ace_age  | int(11)  | NO   |     | NULL    |       |
          +----------+----------+------+-----+---------+-------+

          3. 指定默认值
           mysql> create table aceitems( ace_num int not null, ace_item int not null, ace_id char(10) not null, ace_name char(20) not null, ace_age int not null default 18, primary key (ace_num, ace_item)) engine=InnoDB;
           Query OK, 0 rows affected (0.05 sec)

          +----------+----------+------+-----+---------+-------+
          | Field    | Type     | Null | Key | Default | Extra |
          +----------+----------+------+-----+---------+-------+
          | ace_num  | int(11)  | NO   | PRI | NULL    |       |
          | ace_item | int(11)  | NO   | PRI | NULL    |       |
          | ace_id   | char(10) | NO   |     | NULL    |       |
          | ace_name | char(20) | NO   |     | NULL    |       |
          | ace_age  | int(11)  | NO   |     | 18      |       |
          +----------+----------+------+-----+---------+-------+

          4. 引擎类型
             1. InnoDB 是一个可靠的事务处理引擎, 他不支持全文本搜索.
             2. MEMORY 在功能等同于 MyISAM, 但由于数据存储在内存中, 速度很快.
             3. MyISAM 是一个性能极高的引擎, 它支持全文本搜索, 但不支持事务处理.

      更新表
           mysql> alter table vendors add vend_phone char(20);
           Query OK, 0 rows affected (0.11 sec)
           Records: 0  Duplicates: 0  Warnings: 0
          
          +--------------+----------+------+-----+---------+----------------+
          | Field        | Type     | Null | Key | Default | Extra          |
          +--------------+----------+------+-----+---------+----------------+
          | vend_id      | int(11)  | NO   | PRI | NULL    | auto_increment |
          | vend_name    | char(50) | NO   |     | NULL    |                |
          | vend_address | char(50) | YES  |     | NULL    |                |
          | vend_city    | char(50) | YES  |     | NULL    |                |
          | vend_state   | char(5)  | YES  |     | NULL    |                |
          | vend_zip     | char(10) | YES  |     | NULL    |                |
          | vend_country | char(50) | YES  |     | NULL    |                |
          | vend_phone   | char(20) | YES  |     | NULL    |                |
          +--------------+----------+------+-----+---------+----------------+
          
           mysql> alter table vendors drop column vend_phone;
           Query OK, 0 rows affected (0.11 sec)
           Records: 0  Duplicates: 0  Warnings: 0

          +--------------+----------+------+-----+---------+----------------+
          | Field        | Type     | Null | Key | Default | Extra          |
          +--------------+----------+------+-----+---------+----------------+
          | vend_id      | int(11)  | NO   | PRI | NULL    | auto_increment |
          | vend_name    | char(50) | NO   |     | NULL    |                |
          | vend_address | char(50) | YES  |     | NULL    |                |
          | vend_city    | char(50) | YES  |     | NULL    |                |
          | vend_state   | char(5)  | YES  |     | NULL    |                |
          | vend_zip     | char(10) | YES  |     | NULL    |                |
          | vend_country | char(50) | YES  |     | NULL    |                |
          +--------------+----------+------+-----+---------+----------------+

        查看表外键
         mysql> show create table orderitems \G
*************************** 1. row ***************************
            Table: orderitems
        Create Table: CREATE TABLE `orderitems` (
          `order_num` int(11) NOT NULL,
          `order_item` int(11) NOT NULL,
          `prod_id` char(10) NOT NULL,
          `quantity` int(11) NOT NULL,
          `item_price` decimal(8,2) NOT NULL,
          PRIMARY KEY (`order_num`,`order_item`),
          KEY `fk_orderitems_products` (`prod_id`),
          CONSTRAINT `fk_orderitems_orders` FOREIGN KEY (`order_num`) REFERENCES `orders` (`order_num`),
          CONSTRAINT `fk_orderitems_products` FOREIGN KEY (`prod_id`) REFERENCES `products` (`prod_id`)
          ) ENGINE=InnoDB DEFAULT CHARSET=utf8
         1 row in set (0.00 sec)

        删除表
         mysql> drop table customes;

        重命名表(支持多表重命名)
         mysql> rename table ace to ACEE;
         Query OK, 0 rows affected (0.03 sec)
```

```c++
day-2024-7-16
        使用视图
           
           1. 视图
             为什么使用视图？
              1. 重用 SQL 语句.
              2. 简化复杂的 SQL 操作.
              3. 使用表的组成部分而不是整个表.
              4. 保护数据.
              5. 更改数据格式和表示.
            
             视图的规则和限制？
              1. 与表一样, 视图必须唯一命名.
              2. 对于可以创建的视图数目没有限制.
              3. 为了创建视图, 必须具有足够的访问权限.
              4. 视图可以嵌套, 即可以利用其他视图中检索数据的查询来构造一个视图.
              5. order by 可以用在视图中, 但如果该视图检索数据 select 中也有 order by, 那么该视图的 order by 会被覆盖.
              6. 视图不能索引, 也不能有关联的触发器或默认值.
              7. 视图可以和表一起使用.
            
            2. 创建视图
               利用视图简化复杂的联结

              mysql> create view productcustomers as select cust_name, cust_contact, prod_id
                   from customers, orders, orderitems where customers.cust_id=orders.cust_id
                   and orderitems.order_num=orders.order_num;
              Query OK, 0 rows affected (0.05 sec)

              mysql> select cust_name, cust_contact from productcustomers where prod_id="TNT2";
                    +----------------+--------------+
                    | cust_name      | cust_contact |
                    +----------------+--------------+
                    | Coyote Inc.    | Y Lee        |
                    | Yosemite Place | Y Sam        |
                    +----------------+--------------+
               
               用视图重新格式化检索出来的数据

               mysql> select concat(RTrim(vend_name),"(", RTrim(vend_country), ")") as vend_title from vendors order by vend_name;
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
                
               mysql> create view vendorlocations as select concat(RTrim(vend_name), "(", RTrim(vend_country),")") as
                     vend_title from vendors order by vend_name;
                    Query OK, 0 rows affected (0.03 sec)
                
               mysql> select * from vendorlocations;
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

              用视图过滤掉不想要的数据
                
               mysql> create view customeremaillist as select cust_id, cust_name cust_email
                    from customers where cust_email is not NULL;
                Query OK, 0 rows affected (0.03 sec)

               mysql> select * from customeremaillist;
                    +---------+----------------+
                    | cust_id | cust_email     |
                    +---------+----------------+
                    |   10001 | Coyote Inc.    |
                    |   10003 | Wascals        |
                    |   10004 | Yosemite Place |
                    +---------+----------------+

            使用视图与计算字段
               mysql> select prod_id, quantity, item_price, quantity*item_price
                    as expanded_price from orderitems where order_num=20005;
                    +---------+----------+------------+----------------+
                    | prod_id | quantity | item_price | expanded_price |
                    +---------+----------+------------+----------------+
                    | ANV01   |       10 |       5.99 |          59.90 |
                    | ANV02   |        3 |       9.99 |          29.97 |
                    | TNT2    |        5 |      10.00 |          50.00 |
                    | FB      |        1 |      10.00 |          10.00 |
                    +---------+----------+------------+----------------+

               mysql> create view orderitemsexpanded as select order_num, prod_id,
                    quantity, item_price, quantity*item_price as expanded_price
                    from orderitems;
               Query OK, 0 rows affected (0.03 sec)
               
               mysql> select * from orderitemsexpanded where order_num=20005;
                    +-----------+---------+----------+------------+----------------+
                    | order_num | prod_id | quantity | item_price | expanded_price |
                    +-----------+---------+----------+------------+----------------+
                    |     20005 | ANV01   |       10 |       5.99 |          59.90 |
                    |     20005 | ANV02   |        3 |       9.99 |          29.97 |
                    |     20005 | TNT2    |        5 |      10.00 |          50.00 |
                    |     20005 | FB      |        1 |      10.00 |          10.00 |
                    +-----------+---------+----------+------------+----------------+

            更新视图

            并非所有视图都是可更新的. 如果MySQL 不能正确地确定被更新的基数据, 则不允许更新. 
            这意味着, 如果视图有如下操作, 则不能进行视图的更新:
              1. 分组 (使用 group by 和 having).
              2. 联结.
              3. 子查询.
              4. 并.
              5. 聚集函数(Min() count() sum()) 等.
              6. distinct.
              7. 导出列.

      视图为虚拟的表. 他们包含的不是数据而是根据需要检索数据的查询. 视图提供了一种 MySQL 的select 语句层次的封装,
      可以用来简化数据查询以及重新格式化基础数据和保护基础数据.       
``` 

```c++
        使用存储过程

          1. 存储过程
             存储过程简单来说, 就是为以后的使用而保存的一条或多条 MySQL 语句的集合. 可将其视为批文件, 虽然它们的作用不仅限于批处理.
            
          2. 为什么要使用存储过程
             (1)、 通过把处理封装在容易使用的单元中, 简化复杂的操作.
             (2)、 由于不要求返回建立一系列处理步骤, 这保证了数据完整性. (防止错误)
             (3)、 简化对变动的管理. (安全性)
             (4)、 提高性能, 使用存储过程比使用单独的 SQL 语句要快.
             (5)、存在一些只能在单个请求中的 MySQL 元素和特性, 存储过程可以使用它们来编写功能更强更灵活的代码.
          
          总之, 存储过程三个主要好处: 简单、安全、高性能.

          缺点: 
             复杂和权限.
            
          3.使用存储过程
              (1)、 执行存储过程
               MySQL 称存储过程的执行为调用, 因此 MySQL 执行存储过程的语句为 CALL.

               mysql> call productpricing(@pricelow,@pricehigh,@priceaverage);

              (2)、创建存储过程
               mysql> create procedure productpricing() select avg(prod_price) as priceaverage  from products;
               Query OK, 0 rows affected (0.03 sec)
               
               // MySQL 默认的语句分隔符是 ; 这么begin 和 end 就不会成为存储过程的成分.
               // 解决办法是临时更改命令行实用程序的语句分隔符(除  \ 外, 任意字符都可以用作语句分隔符), 如下:
               
               mysql> delimiter //
               mysql> create procedure productprice()
                    begin
                          select avg(prod_price) as priceaverage
                          from products;
                    end //
               Query OK, 0 rows affected (0.03 sec)

               mysql> delimiter ;

               mysql> call productpricing();
                    +--------------+
                    | priceaverage |
                    +--------------+
                    |    16.133571 |
                    +--------------+
              
              (3)、 删除存储过程
               mysql> drop procedure productpricing;
               Query OK, 0 rows affected (0.03 sec)

              (4)、 使用参数
               mysql> create procedure productpricing(
                   out pl decimal(8,2),
                   out ph decimal(8,2),
                   out pa decimal(8,2)
                   )
                   begin
                     select min(prod_price)
                     into pl
                     from products;
                     select max(prod_price)
                     into ph
                     from products;
                     select avg(prod_price)
                     into pa
                     from products;
                   end //
              
               mysql> call productpricing(@pricelow,@pricehigh,@priceaverage);
               Query OK, 1 row affected, 1 warning (0.03 sec)

               mysql> select @priceaverage;
                  +---------------+
                  | @priceaverage |
                  +---------------+
                  |         16.13 |
                  +---------------+

               mysql> select @pricehigh, @pricelow, @priceaverage;
                  +------------+-----------+---------------+
                  | @pricehigh | @pricelow | @priceaverage |
                  +------------+-----------+---------------+
                  |      55.00 |      2.50 |         16.13 |
                  +------------+-----------+---------------+

               mysql> create procedure ordertotal(
                      in onumber int,
                      out ototal decimal(8,2)
                      )
                      begin
                         select sum(item_price * quantity)
                         from orderitems
                         where order_num = onumber
                         into ototal;
                      end//
                
               mysql> call ordertotal(20005, @total);
               Query OK, 1 row affected (0.00 sec)

               mysql> select @total;
                    +--------+
                    | @total |
                    +--------+
                    | 149.87 |
                    +--------+

          4.  创建智能存储过程
            ..... P183  ....

              mysql> show procedure status; // 查看存储过程信息.；
          
          5. 检查存储过程
              mysql> show create procedure productpricing \g // 内容过多.

```

```c++
          使用游标
            1. 创建游标
              mysql> delimiter //
              mysql> create procedure processorders()
                    begin
                       declare ordernumbers cursor
                       for
                       select order_num from orders;
                    end //
              Query OK, 0 rows affected (0.03 sec)
            
            2. 打开和关闭游标

             mysql> open ordernumbers;
             mysql> close ordernumbers;

            mysql> create procedure processorders()
                  begin
                    declare ordernumbers cursor
                    for
                    select order_num from orders;
                    open ordernumbers;
                    close ordernumbers;
                  end //
            Query OK, 0 rows affected (0.00 sec)
```

```c++
          触发器
            1. 创建触发器
             mysql> create trigger newaccount
                    after insert on account
                    for each row
                    begin
                      insert into account(name, balance)
                      values("id added", 2090);
                    end //
            Query OK, 0 rows affected (0.03 sec)
              
            2. 删除触发器
             mysql> drop trigger newaccount;
            
            3. 使用触发器
             (1)、 insert 触发器
               ... 看不懂, 执行都err..

```

```c++
day - 2024 - 7 - 19
        管理事务处理
          1. 事务处理术语
               事务: 指一组 SQL 语句.
               回退: 指撤销指定 SQL 语句的过程.
               提交: 指将未存储的 SQL 语句结果写入数据库表.
               保留点: 指事务处理中设置的临时占位符,可以对它发布回退.
          
          2. 控制事务处理

            mysql> start transaction; // 开启事务
            Query OK, 0 rows affected (0.02 sec)

            1). 使用 rollback
            
            mysql> select * from ordertotals;
            +------+
            | id   |
            +------+
            |    1 |
            |    2 |
            |    3 |
            +------+
            3 rows in set (0.00 sec)

            mysql> start transaction;
            Query OK, 0 rows affected (0.00 sec)

            mysql> delete from ordertotals;
            Query OK, 3 rows affected (0.02 sec)

            mysql> select * from ordertotals;
            Empty set (0.00 sec)

            mysql> rollback;
            Query OK, 0 rows affected (0.01 sec)

            mysql> select * from ordertotals;
            +------+
            | id   |
            +------+
            |    1 |
            |    2 |
            |    3 |
            +------+
            3 rows in set (0.00 sec)
          
          2). 使用 commit 
           
           mysql> start transaction;
           Query OK, 0 rows affected (0.00 sec)

           mysql> delete from orderitems where order_num = 200010;
           Query OK, 0 rows affected (0.03 sec)

           mysql> delete from orders where order_num = 200010;
           Query OK, 0 rows affected (0.00 sec)

           mysql> commit;
           Query OK, 0 rows affected (0.00 sec)

          3). 使用保留点

            mysql> start transaction;
           Query OK, 0 rows affected (0.00 sec)

           mysql> savepoint d1;
           Query OK, 0 rows affected (0.00 sec)

           mysql> rollback to d1;
           Query OK, 0 rows affected (0.00 sec)


          4). 更改默认的提交行为

            mysql> set autocommit=0;
           Query OK, 0 rows affected (0.00 sec)

           mysql> set autocommit=1;
           Query OK, 0 rows affected (0.00 sec)

        autocommit: 是否自动提交更改.
```