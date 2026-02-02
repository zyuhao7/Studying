from 学生管理系统.student import Student


class StudentManager:
    def __init__(self):
        self.student = []

    # 1. 添加学员
    def add_student(self):
        sid = int(input("请输入学号:"))
        name = input("请输入名字:")
        age = int(input("请输入年龄:"))
        self.student.append(Student(sid, name, age))
        print("✅ 添加成功")

    # 2.修改学员
    def modify_student(self):
        sid = int(input("请输入要修改的学号:"))
        for stu in self.student:
            if stu.sid == sid:
                stu.name = input("新名字:")
                stu.age = int(input("新年龄:"))
                print("✅ 修改成功")
                return
        print("❌ 未找到该学员")

    # 3. 删除学员
    def del_student(self):
        sid = int(input("请输入要删除的学号:"))
        for stu in self.student:
            if stu.sid == sid:
                self.student.remove(stu)
                print("✅ 删除成功")
                return
        print("❌ 未找到该学员")

    # 4. 查询某个学员
    def query_student(self):
        sid = int(input("请输入要查询的学号:"))
        for stu in self.student:
            if stu.sid == sid:
                print(stu)
                return
        print("❌ 未找到该学员")

    # 5 显示所有学员
    def show_all(self):
        if not self.student:
            print("📭 当前没有学员")
            return
        for stu in self.student:
            print(stu)
    # 6 保存信息（简单示例）
    def save(self):
        with open("students.txt", "w", encoding="utf-8") as f:
            for stu in self.student:
                f.write(f"{stu.sid},{stu.name},{stu.age}\n")
        print("💾 保存成功")
