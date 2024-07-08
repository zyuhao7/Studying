\```c++

 day-2024-7-8

   使用子查询

​    利用子查询进行过滤

​    mysql> select order_num from orderitems where prod_Id = "TNT2";

​     +-----------+

​     | order_num |

​     +-----------+

​     |   20005 |

​     |   20007 |

​     +-----------+

​    

​    mysql> select cust_id from orders where order_num in (20005,20007);

​     +---------+

​     | cust_id |

​     +---------+

​     |  10001 |

​     |  10004 |

​     +---------+



   mysql> select cust_id from orders where order_num in (select order_num from orderitems where prod_id="TNT2");

​     +---------+

​     | cust_id |

​     +---------+

​     |  10001 |

​     |  10004 |

​     +---------+

   mysql> select cust_name, cust_contact from customers where cust_id in(10001,10004);

​     +----------------+--------------+

​     | cust_name    | cust_contact |

​     +----------------+--------------+

​     | Coyote Inc.   | Y Lee     |

​     | Yosemite Place | Y Sam     |

​     +----------------+--------------+

   

   mysql> select cust_name, cust_contact from customers where cust_id in (select cust_id from orders where

  -> order_num in (select order_num from orderitems where prod_id = "TNT2"));

​     +----------------+--------------+

​     | cust_name    | cust_contact |

​     +----------------+--------------+

​     | Coyote Inc.   | Y Lee       |

​     | Yosemite Place | Y Sam      |

​     +----------------+--------------+

    mysql> select cust_name, cust_state,(select count(*) from orders where orders.cust_id=customers.cust_id) as
    -> orders from customers order by cust_name;

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
    -> from customers order by cust_name;
    
        +----------------+------------+--------+
        | cust_name      | cust_state | orders |
        +----------------+------------+--------+
        | Coyote Inc.    | MI         |      5 |
        | E Fudd         | IL         |      5 |
        | Mouse House    | OH         |      5 |
        | Wascals        | IN         |      5 |
        | Yosemite Place | AZ         |      5 |
        +----------------+------------+--------+




\```