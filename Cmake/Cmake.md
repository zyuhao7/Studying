## Cmake

### centos下cmake版本过低

```shell
https://cmake.org/files/ #Cmake下载地址

cmake --version   #检查cmake版本

yum autoremove cmake  #卸载旧版cmake

mkdir /opt/cmake  #创建目录

cd  /opt/cmake   #进入目录

wget http://www.cmake.org/files/v3.16/cmake-3.16.6.tar.gz #获取安装包

tar -xzvf cmake-3.16.6.tar.gz #解压缩

cd cmake-3.16.6

./bootstrap #执行

make
make install

ln -s /usr/local/bin/cmake /usr/bin  #链接

### 出现 NOT FIND OPENSSL 
yum install openssl-devel 
```



> ​	上诉文件目录结构

![image-20240326142117032](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240326142117032.png)

> ​	添加 CMakeLists.txt文件



```bash	
cmake_minimum_required(VERSION 3.0) # 指定使用的 cmake 的最低版本

project(CALC)   #定义工程名称，并可指定工程的版本、工程描述、web主页地址、支持的语言（默认情况支持所有语言），如果不需要这些都是可以忽略的，只需要指定出工程名字即可。

# add_executable(可执行程序名 源文件名称) 源文件用空格或者;隔开
add_executable(test add.c div.c main.c mult.c sub.c)

# 样式1
add_executable(app add.c div.c main.c mult.c sub.c)
# 样式2
add_executable(app add.c;div.c;main.c;mult.c;sub.c)

```



> ​	执行 Cmake 命令

```shell
#当执行cmake命令之后，CMakeLists.txt 中的命令就会被执行，所以一定要注意给cmake 命令指定路径的时候一定不能出错。

#cmake + CMakeLists.txt 路径 自动将生成文件保存在 cmake当前路径 make 编译生成可执行文件

#如果在当前路径下创建一个 build 文件, 进入 build 目录中, 执行 cmake .. 就将中间文件生成在 build 目录中
```



![image-20240326143310046](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240326143310046.png)	



> ​	Set

```C++
// 方式1: 各个源文件之间用空格隔开.
// set(SRC_LIST add.c div.c main.c mult.c sub.c)

// 方式2: 各个原文件之间使用 ; 隔开.
set(SRC_LIST add.c;div.c;main.c;mult.c;sub.c)
add_exectable(test ${SRC_LIST}) 
    
//增加-std=c++11
set(CMAKE_CXX_STANDARD 11)
//增加-std=c++14
set(CMAKE_CXX_STANDARD 14)
//增加-std=c++17
set(CMAKE_CXX_STANDARD 17)

//增加-std=C++11
cmake CMakeLists.txt文件目录 -DCMAKE_CXX_STANDARD=11
    
// 指定输出的路径
    
set(HOME /root/Cmake/Code) // 定义一个变量用于存储一个绝对路径.
set(EXECUTABLE_OUTPUT_PATH ${HOME}/aa/bb/cc) // 将拼接好的路径设置给 EXECUTABLE_OUTPUT_PATH

```

![image-20240329152758826](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240329152758826.png)

> ​	搜索文件

```shell

aux_source_directory(< dir > < variable >)
方式1:
dir 搜索的目录
variable 将从 dir 目录下搜索到的源文件列表存储到该变量中.

## 搜索 src 目录下的源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
add_executable (test ${SRC_LIST})

方式2:
file(GLOB/GLOB_RECURSE 变量名 要搜索的文件路径和文件类型)
## GLOB 将指定目录下搜索到的满足条件的所有文件名生成一个列表, 并将其存储到变量中.
## GLOB_RECURSE 递归搜索指定目录, 将搜索到的满足条件的文件名生成一个列表,并将其存储到变量中.

## CMAKE_CURRENT_SOURCE_DIR 宏表示当前访问的 CMakeLists.txt 文件所在的路径.
file {GLOB MAIN_HEAD "${CMAKE_CURRENT_DIR}/src/*.h"}  ##引号可加可不加.

## 包含头文件
include_directories(headpath)




cmake_minimum_required(VERSION 3.10)
  2 project(MyProject)
  3 set(CMAKE_CXX_STANDARD 11)
  4 set(HOME /root/Cmake/Code)
  5 set(EXECUTABLE_OUTPUT_PATH ${HOME}/aa/bb/cc)
  6 include_directories(${PROJECT_SOURCE_DIR}/include)
  7 file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
  8 add_executable(app ${SRC_LIST})  

```



> ​	**制作动态库或静态库**

```shell
cmake_minimum_required(VERSION 3.10)
project(CALC)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_library(calc SHARED ${SRC_LIST}) # SHARED 动态库.

# 为动态库指定输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib) #失效.

# 动静态库都适用
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

```

![image-20240330174818868](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240330174818868.png)

```shell
# 链接静态库
link_directories(${PROJECT_SOURCE_DIR}/lib) # 包含静态库路径.
link_libraries(calc)
add_executable(app ${SRC_LIST})

#链接动态库
#在cmake中指定要链接的动态库的时候，应该将命令写到生成了可执行文件之后
add_executable(app ${SRC_LIST})
target_link_libraries(app pthread)
#使用 target_link_libraries 命令就可以链接动态库，也可以链接静态库文件
# 当链接的库既有自己的，又有系统的.
# 指定要链接的动态库的路径
link_directories(${PROJECT_SOURCE_DIR}/lib)
```



> ​	**日志**



```bash
# 输出一般日志信息.
message(STATUS "source path: ${PROJECT_SOURCE_DIR}")

#输出警告信息
message(WARNING "source path: ${PROJECT_SOURCE_DIR}")

#输出错误信息
message(FATAL_ERROR "source path: ${PROJECT_SOURCE_DIR}")
```

![image-20240406195535669](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240406195535669.png)



> ​	 **变量操作**

```shell	
# 使用 set 拼接

set(变量名1 ${变量名1} ${变量名2}...)
#将从第二个参数开始往后所有的字符串进行拼接, 最后将结果存储到第一个参数中, 如果第一个参数中原来有数据会覆盖

###### cmake 截取.
cmake_minimum_required(VERSION 3.10)
project(TEST)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# 指定要链接的动态库的路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(TEMP "Hello, world")

add_executable(app ${SRC_LIST})
set(SRC ${SRC_LIST}  ${TEMP})
message(STATUS "message: ${SRC}")

target_link_libraries(app pthread calc)

set(tmp1 a;b;c;d;e)
set(tmp2 a b c d e)
message(${tmp1})
message(${tmp2})
```

![image-20240406200256995](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240406200256995.png)

![image-20240406200210728](C:\Users\徐浩\AppData\Roaming\Typora\typora-user-images\image-20240406200210728.png)





```shell
#使用 list 拼接

list(APPEND SRC ${SRC_1} ${SRC_2} ${TEMP}) # 等价于set拼接.

#字符串移除
list(REMOVE_ITEM SRC_1 ${PROJECT_SOURCE_DIR}/main.c)

```



> ​	**宏定义**

```C++	
// 在gcc/g++命令中通过参数 -D指定出要定义的宏的名字，这样就相当于在代码中定义了一个宏，其名字为DEBUG

// 在CMake中我们也可以做类似的事情，对应的命令叫做add_definitions
// 自定义 DEBUG 宏
add_definitions(-DDEBUG)
add_executable(app ./test.c)
```



