# 读取 CSV 文件并将其转为字典格式输出
import csv
import json
import multiprocessing
import os
import threading
from turtledemo.penrose import start

import requests
from asyncio import timeout
from textwrap import indent

from fontTools.ttx import process

from MultiThread import threads

# def csv_to_dict(file_path):
#     with open(file_path, mode = 'r', encoding='utf-8') as file:
#         reader = csv.DictReader(file)
#         data = [row for row in reader]
#     return data
#
# file_path = "data.csv"
# Result = csv_to_dict(file_path)
# print(Result)

# 解析 JSON 文件，将其转为字典，并打印所有内容
# def json_to_dict(file_path):
#     with open(file_path, mode = 'r',encoding='utf-8') as file:
#         data = json.load(file)
#     return data
#
# file_path = "data.json"
# result = json_to_dict(file_path)
# print(json.dumps(result, indent=4, ensure_ascii=False))

# 编写多线程下载器，模拟爬取网页的图片，将下载的图片保存到本地。

# 创建保存图片的目录
# SAVE_DIR = "images"
# os.makedirs(SAVE_DIR, exist_ok=True)
#
# # 要下载的图片 URL 列表（示例）
# image_urls = [
#     "https://picsum.photos/300/200",  # 随机图片 URL 示例
#     "https://picsum.photos/300/201",
#     "https://picsum.photos/300/202",
#     "https://picsum.photos/300/203",
#     "https://picsum.photos/300/204"
# ]
#
# def download_image(url, index):
#     """下载并保存图片"""
#     try:
#         response = requests.get(url, stream=True, timeout=10)  # 获取图片内容
#         if response.status_code == 200:
#             file_path = os.path.join(SAVE_DIR, f"image_{index}.jpg")
#             with open(file_path, "wb") as file:
#                 for chunk in response.iter_content(1024):  # 分块写入
#                     file.write(chunk)
#             print(f"✅ 下载成功: {file_path}")
#         else:
#             print(f"❌ 下载失败: {url}")
#     except Exception as e:
#         print(f"⚠️  错误: {e}")
#
# def main():
#     threads = []
#     for i, url in enumerate(image_urls):
#         t = threading.Thread(target=download_image, args=(url, i))
#         t.start()
#         threads.append(t)
#
#     for t in threads:
#         t.join()  # 等待所有线程完成
#
#     print("🎉 所有图片下载完成!")
#
# if __name__ == "__main__":
#     main()

# 使用 multiprocessing 实现简单的并行计算任务，比如计算一组数的平方
# import multiprocessing
#
# def square(n):
#     print(f"进程{multiprocessing.current_process().name} 计算: {n}² = {n * n}")
#     return n * n
# if __name__ == "__main__":
#     numbers = [1, 2, 3, 4, 5]
#     num_workers = min(len(numbers), multiprocessing.cpu_count())
#
#     with multiprocessing.Pool(processes=num_workers) as pool:
#         results = pool.map(square, numbers)
#     print("计算结果:", results)