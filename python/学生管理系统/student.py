class Student:
    def __init__(self, sid:int, name: str, age:int):
        self.sid = sid
        self.name = name
        self.age = age

    def __str__(self):
        return f"学号:{self.sid}, 姓名:{self.name}, 年龄:{self.age}"

