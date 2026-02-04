"""
    day-2026-2-4
    闭包 = 函数 + 它"记住"的外部作用域变量

    三个条件:
        1.嵌套函数
        2.使用了外层函数的变量
        3.外层函数返回内层函数

"""
from anyio import sleep
from wrapt import decorator


def outer():
    x = 10
    def inner():
        return x
    return inner

f = outer()
print(f())  # 10

# example: err
funcs = []
for i in range(3):
    def f():
        return i
    funcs.append(f)

print([f() for f in funcs]) # 2 2 2 而不是 1 2 3, Python 闭包捕获的是变量本身, 而不是当前的值.

# example:true
funcs = []
for i in range(3):
    def f(x=i):
        return x
    funcs.append(f)
print([f() for f in funcs])  # [0, 1, 2]

# nonlocal：闭包里修改外部变量 ≈ C++ 捕获引用 &cnt
def counter():
    cnt = 0
    def inc():
        nonlocal  cnt
        cnt +=  1
        return cnt
    return inc
c = counter()

print(c()) # 1
print(c()) # 2

"""
    装饰器 = 使用闭包，对函数“包装增强”的语法糖
    
"""

# 传统
# def my_decorator(func):
#     def wrapper():
#         print("before")
#         func()
#         print("after")
#     return wrapper
#
# def hello():
#     print("hello")
#
# hello = my_decorator(hello)
# hello()

#@语法糖
def my_decorator(func):
    def wrapper():
        print("before")
        func()
        print("after")
    return wrapper

@my_decorator #等价于 hello = my_decorator(hello)
def hello():
    print("hello")

hello()



import time
from functools import wraps

def time_cost(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        print(f"{func.__name__} cost {time.time() - start:.3f}s")
        return result
    return wrapper

@time_cost
def add():
    x = 10
    y = 20
    return x + y

def cache(func):
    memo = {}
    def wrapper(x):
        if x not in memo:
            memo[x] = func(x)
        return memo[x]
    return wrapper

@cache
@time_cost
def fib(n):
    if n <= 1:
        return n
    return fib(n-1) + fib(n-2)

print(fib(100))