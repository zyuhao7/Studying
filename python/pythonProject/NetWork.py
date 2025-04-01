#  发送 HTTP 请求
# 2.1 发送 GET 请求
import requests

# response = requests.get("https://jsonplaceholder.typicode.com/posts/1")
# print(response.status_code)
# print(response.json())

# 2.2 发送 POST 请求
# url = "https://jsonplaceholder.typicode.com/posts"
# data = {"title": "foo", "body": "bar", "userId": 1}
#
# response = requests.post(url, json=data)  # 发送 JSON 数据
# print(response.status_code)
# print(response.json())

#  2.3 发送 PUT 请求 -> 更新资源
# url = "https://jsonplaceholder.typicode.com/posts/1"
# data = {"id": 1, "title": "updated", "body": "new content", "userId": 1}
#
# response = requests.put(url, json=data)
# print(response.status_code)
# print(response.json())

# 2.4 发送 DELETE 请求
# url = "https://jsonplaceholder.typicode.com/posts/1"
#
# response = requests.delete(url)
# print(response.status_code)  # 204 表示删除成功

