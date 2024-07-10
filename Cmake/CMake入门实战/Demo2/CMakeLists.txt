cmake_minimum_required(VERSION 2.8)

project(Demo2)

# add_executable(Demo main.cc MathFunction.cc)

# 查找当前目录下的所有源文件 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

#指定生成目标
add_executable(Demo ${DIR_SRCS})
