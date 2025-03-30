from collections import namedtuple, Counter, defaultdict, OrderedDict, ChainMap
from itertools import chain

from PIL.ImImagePlugin import number

# 编写一个简单的函数，求给定列表中的最大值，编写测试代码进行验证。
# def find_max(numbers):
#     if not numbers:
#         raise  ValueError("列表不能为空")
#     max_num = numbers[0]
#     for num in numbers[1:]:
#         if num > max_num:
#             max_num = num
#     return max_num
#
#
# # 测试代码
# if __name__ == "__main__":
#     # 测试用例
#     test_cases = [
#         ([1, 2, 3, 4, 5], 5),  # 普通整数列表
#         ([-1, -5, -3, -2], -1),  # 负数列表
#         ([3.14, 2.71, 1.618], 3.14),  # 浮点数列表
#         ([42], 42),  # 单元素列表
#         ([0, 0, 0, 0], 0),  # 全零列表
#         ([1, 3, 2], 3),  # 最大值在中间
#     ]
#
#     # 执行测试
#     for i, (input_list, expected) in enumerate(test_cases, 1):
#         try:
#             result = find_max(input_list)
#             assert result == expected, f"测试失败: 期望 {expected}, 得到 {result}"
#             print(f"测试用例 {i}: 通过 (输入: {input_list}, 输出: {result})")
#         except AssertionError as e:
#             print(f"测试用例 {i}: 失败 - {e}")
#         except Exception as e:
#             print(f"测试用例 {i}: 发生意外错误 - {type(e).__name__}: {e}")
#
#     # 测试空列表异常
#     try:
#         find_max([])
#         print("空列表测试: 失败 - 未引发异常")
#     except ValueError:
#         print("空列表测试: 通过 - 正确引发 ValueError")
#     except Exception as e:
#         print(f"空列表测试: 失败 - 引发错误的异常 {type(e).__name__}")

# 学习 collections 模块
# 1. namedtuple - 命名元组
# 用途：创建具有命名字段的元组子类

# Point = namedtuple('Point', ['x', 'y'])
# p = Point(11, y=22)
# print(p.x, p.y)
# print(p[0],p[1])

from collections import  deque
# 2. deque - 双端队列
# d = deque(['A','B','C'])
# d.append('D')
# d.appendleft('Z')
# d.pop()
# d.popleft()
# d.rotate(1) #向右旋转一步
# d.rotate(-1) #左

# 3. Counter - 计数器
# 用途：统计可哈希对象的数量
# c = Counter('abracadabra')
# print(c)
# print(c.most_common(2))
# c.update('aaa')
# print(c)
# c.subtract('a')
# print(c)

# 4. defaultdict - 默认字典
# 用途：为不存在的键提供默认值

# dd = defaultdict(int) # 默认值为0的字典
# dd['a'] += 1
# print(dd)
#
# dl = defaultdict(list)
# dl['colors'].append('red')
# dl['colors'].append('green')
# dl['fruits'].append('banana')
# print(dl)

#5. OrderedDict - 有序字典
# 用途：记住键的插入顺序（Python 3.7+ 普通 dict 也已有序）

# od = OrderedDict()
# od['z'] = 1
# od['a'] = 2
# od['c'] = 3
# print(list(od.keys()))
# od.move_to_end('a')
# print(list(od.keys()))
# od.popitem(last = False) #默认删除最后一个, 置为 False 删除第一个
# print(list(od.keys()))

#6. ChainMap - 链式映射
# 用途：将多个字典/映射组合成单个视图
# dict1 = {'a' : 1, 'b' : 2}
# dict2 = {'c' : 3, 'd' : 4}
#
# chain = ChainMap(dict1, dict2)
#
# print(chain['b'])
# print(chain['c'])
#
# new_chain = chain.new_child({'d':5})
# print(new_chain)


# 用 groupby 分组计算一个列表中的相邻相同元素。
from itertools import groupby

def group_adjacent_elements(lst):
    """
    分组计算列表中的相邻相同元素

    参数:
        lst: 包含任意元素的列表

    返回:
        一个生成器，生成 (元素, 连续出现次数) 的元组
    """
    return ((key, len(list(group))) for key, group in groupby(lst))

# 示例1: 数字列表
numbers = [1, 1, 2, 3, 3, 3, 4, 2, 2, 1]
result = list(group_adjacent_elements(numbers))
print(result)
# 输出: [(1, 2), (2, 1), (3, 3), (4, 1), (2, 2), (1, 1)]

# 示例2: 字符列表
chars = ['a', 'a', 'b', 'c', 'c', 'a', 'a', 'a']
result = list(group_adjacent_elements(chars))
print(result)
# 输出: [('a', 2), ('b', 1), ('c', 2), ('a', 3)]

from functools import reduce


def cumulative_sum(lst):
    """
    使用 reduce 计算列表中所有元素的累积和

    参数:
        lst: 包含数字的列表

    返回:
        所有元素的累积和
    """
    return reduce(lambda x, y: x + y, lst, 0)
print([])
numbers = [1, 2, 3, 4, 5]
result = cumulative_sum(numbers)
print(result)  # 输出: 15 (1+2+3+4+5)