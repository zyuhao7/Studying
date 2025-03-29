# 1. 列表（List）
# 特点：
#
# 有序、可变（元素可增删改）、支持索引访问
#
# 适用于存储多个相关的元素
#
# nums = [1, 2, 3, 4, 5]
# print(nums[0])
# nums.append(6)
# nums.remove(3)
# print(nums[1:4])
# for num in nums:
#     print(num)

# 2. 元组（Tuple）
# 特点：
#
# 有序、不可变（元素不能修改）
#
# 适用于存储不希望被修改的数据，如坐标、配置信息等

# point =(10, 20)
# print(point[0])
# x, y = point
# print(x, y)

# 3. 字典（Dictionary, dict）
# 特点：
#
# 键值对（key-value） 存储，无序（Python 3.7+ 以后是有序的）
#
# 适用于快速查找、存储映射关系

# person = {"name": "Alice", "age": 25, "city": "New York"}
#
# print(person["name"])
#
# person["age"] = 26
# person["gender"] = "Female"
#
# del person["city"]
#
# for key, value in person.items():
#     print(f"{key}: {value}")

# 4. 集合（Set）
# 特点：
#
# 无序、不重复，适用于去重和集合运算（交集、并集等）

# nums_set = {1, 2, 3, 4, 5, 5}
# nums_set.add(6)
# nums_set.remove(3)
#
# A = {1, 2, 3}
# B = {3, 4, 5}
# print(A | B)
# print(A & B)
# print(A - B)

# 5. 栈（Stack）
# 特点：
#
# 后进先出（LIFO, Last In First Out）
#
# append() 作为入栈操作，pop() 作为出栈操作
# st = []
#
# st.append(1)
# st.append(2)
# st.append(3)
# print(st.pop())
# print(st)

# 6. 队列（Queue）
# 特点：
#
# 先进先出（FIFO, First In First Out）
#
# Python 中可以使用 collections.deque 实现

# from collections import deque

# que =  deque()
# que.append(1)
# que.append(2)
# que.append(3)
# print(que.pop()) # 右
# print(que.popleft()) # 左
# print(que)

# 7. 链表（Linked List）
# 特点：
#
# 由节点组成，每个节点包含数据和指向下一个节点的指针
#
# 适用于频繁插入/删除的情况

# class Node:
#     def __init__(self, data):
#         self.data = data
#         self.next = None
#
# class LinkedList:
#     def __init__(self):
#         self.head = None
#
#     def append(self, data):
#         new_node = Node(data)
#         if not self.head:
#             self.head = new_node
#             return
#         tmp = self.head
#         while tmp.next:
#             tmp = tmp.next
#         tmp.next = new_node
#
#     def print_list(self):
#         tmp = self.head
#         while tmp.next:
#             print(tmp.data, end = " -> ")
#             tmp = tmp.next
#         print("None")
#
# l1 = LinkedList()
# l1.append(1)
# l1.append(2)
# l1.append(3)
#
# l1.print_list()

# 8. 堆（Heap）
# 特点：
#
# 优先队列 数据结构，最小堆中最小元素总是位于根
#
# Python 提供 heapq 模块

# import heapq
#
# heap = []
# heapq.heappush(heap, 3)
# heapq.heappush(heap, 1)
# heapq.heappush(heap, 2)
#
# print(heapq.heappop(heap))




