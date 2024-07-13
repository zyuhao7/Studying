cmake_minimum_required(VERSION 2.8)

project(Demo4)

# 加入一个配置头文件, 用于处理 CMake 对源码的设置.
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

# 是否使用自己的 MathFunctions 库
option(USE_MYMATH
    "Use provided math implementation" OFF)

# 是否加入 MathFunctions 库
if(USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory(math)
    set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(USE_MYMATH)

aux_source_directory(. DIR_SRCS)

add_executable(Demo ${DIR_SRCS})
target_link_libraries(Demo ${EXTRA_LIBS})