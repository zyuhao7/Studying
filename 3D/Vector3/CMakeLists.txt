cmake_minimum_required(VERSION 3.10)
project(Vector3Math LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(demo
    main.cpp
    Vector3.cpp
    MathUtil.cpp
    EulerAngles.cpp
    RotationMatrix.cpp
    Quaternion.cpp
    Matrix4x3.cpp
)

if(MSVC)
    target_compile_options(demo PRIVATE /W3)
else()
    target_compile_options(demo PRIVATE -Wall -Wextra)
endif()
