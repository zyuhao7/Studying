"""A beginner-friendly command line calculator.

This script avoids eval on purpose, so each supported operation is handled
explicitly. Run it with:

    python simple_calculator.py
"""

def add(left: float, right: float) -> float:
    return left + right


def subtract(left: float, right: float) -> float:
    return left - right


def multiply(left: float, right: float) -> float:
    return left * right


def divide(left: float, right: float) -> float:
    if right == 0:
        raise ZeroDivisionError("除数不能为 0")
    return left / right


def modulo(left: float, right: float) -> float:
    if right == 0:
        raise ZeroDivisionError("除数不能为 0")
    return left % right


def power(left: float, right: float) -> float:
    return left**right


OPERATIONS = {
    "+": add,
    "-": subtract,
    "*": multiply,
    "/": divide,
    "%": modulo,
    "**": power,
}


def read_number(prompt: str) -> float:
    while True:
        value = input(prompt).strip()
        try:
            return float(value)
        except ValueError:
            print("输入无效，请输入数字，例如 12、3.14 或 -5。")


def read_operator() -> str:
    supported = ", ".join(OPERATIONS)
    while True:
        operator = input(f"请输入运算符({supported}):").strip()
        if operator in OPERATIONS:
            return operator
        print("不支持这个运算符，请重新输入。")


def calculate_once() -> None:
    left = read_number("请输入第一个数字：")
    operator = read_operator()
    right = read_number("请输入第二个数字：")

    try:
        result = OPERATIONS[operator](left, right)
    except ZeroDivisionError as error:
        print(f"计算失败：{error}")
        return

# 使用 :g 格式化数字，去掉不必要的零和小数点
    print(f"计算结果：{left:g} {operator} {right:g} = {result:g}")


def main() -> None:
    print("简单计算器")
    print("支持运算：+  -  *  /  %  **")
    print("输入 q 可以退出。")

    while True:
        command = input("\n按 Enter 开始计算，输入 q 退出：").strip().lower()
        if command == "q":
            print("已退出计算器。")
            break
        calculate_once()


if __name__ == "__main__":
    main()
