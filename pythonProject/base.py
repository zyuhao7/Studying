
import math
print(math.sqrt(16))

x = 5
with open("example.txt", "w") as file:
    file.write("jack Love")

print(x)

# 列表
frutis = ["Apple", "Banana", "Cherry"]
print(frutis)

# 元组
point = (1, 2)
print(point)

# 字典
person = {"name" : "Alice", "age" : "25"}
print(person)

# 集合
nums = {1, 2, 3}
print(nums)

# 2、控制流
# age = 18
#
# if age >= 18:
#     print("Adult")
# else:
#     print("Minor")
#
# for fruit in frutis:
#     print(fruit)
#
# count = 0
# while count < 5:
#     print(count)
#     count += 1
#
# for i in range(5):
#     if i == 2:
#         continue
#     print(i)
#
# def greet(name = "Guest"):
#     return f"Hello, {name}!"
# result = greet("Alice")
# print(result)
# print(greet())
#
# def add_numbers(*args):
#     return sum(args)
#
# Sum = add_numbers(1, 2, 3, 5, 6)
# print(Sum)

# 3、类和对象
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def greet(self):
        return f"Hello, my name is {self.name}."

print(Person("alice", 18).greet())

class Student(Person):
    def __init__(self, name, age, grade):
        super().__init__(name, age)
        self.grade = grade

# 4、异常处理
try:
    result = 20 / 0
except ZeroDivisionError:
    print("Cannot divide by zero.")

# 5、列表推导式
squares = [x ** 2 for x in range(5)]
print(squares)