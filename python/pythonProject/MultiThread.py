import threading
from concurrent.futures.thread import ThreadPoolExecutor
from itertools import count


def print_numbers():
    for i in range(5):
        print(f"thread: {i}")

# 创建线程
# t = threading.Thread(target=print_numbers)
# t.start()
# t.join()

# def task(n):
#     print(f"Processing {n}")
#
# with ThreadPoolExecutor(max_workers=4) as executor:
#     executor.map(task, range(5))

# 线程同步
lock = threading.Lock()
counter = 0
def increase():
    global counter
    with lock:
        counter += 1
threads = [threading.Thread(target=increase) for _ in range(10)]
for t in threads:
    t.start()
for t  in threads:
    t.join()

print("Final Counter : ", counter)

# Python 文件与多线程结合
def write_to_file(filename, text):
    with open(filename, "a") as file:
        file.write(text + "\n")

threads = []
for i in range(5):
    t = threading.Thread(target=write_to_file, args=("example.txt", f"Line {i}"))
    t.start()
    threads.append(t)

for t in threads:
    t.join()
