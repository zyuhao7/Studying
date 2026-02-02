from 学生管理系统.studentManager import StudentManager


def show_menu():
    print("""
======== 学生管理系统 ========
1 添加学员
2 修改学员
3 删除学员
4 查询某个学员
5 显示所有学员
6 保存信息
0 退出系统
============================
""")


class Application:
    def __init__(self):
        self.manager = StudentManager()

    def run(self):
        while True:  # ← 反复多次使用
            show_menu()
            choice = input("请选择功能: ")

            if choice == "1":
                self.manager.add_student()
            elif choice == "2":
                self.manager.modify_student()
            elif choice == "3":
                self.manager.del_student()
            elif choice == "4":
                self.manager.query_student()
            elif choice == "5":
                self.manager.show_all()
            elif choice == "6":
                self.manager.save()
            elif choice == "0":
                print("👋 退出系统")
                break
            else:
                print("❌ 无效选择")


if __name__ == "__main__":
    app = Application()
    app.run()