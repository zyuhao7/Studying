# file = open("example.txt", "r") #只读

with open("example.txt", "r") as file:
    content = file.read()
    lines = file.readlines()
    print(content)
    print(lines)

with open("example.txt", "a") as file:
    file.write("hello world! ")

with open("example.txt", "r") as file:
    for line in file:
        print(line.strip())