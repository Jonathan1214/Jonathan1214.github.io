---
title: cmake 的基本使用方法
copyright: true
notshow: false
date: 2022-06-19 16:05:52
updated:
categories:
tags:
  - cmake
  - usage
---

关于 cmake 的使用，如果要讲细的话可以说上很多，这里通过一个简单的例子介绍如何快速写一个可以跑起来的 cmake 脚本。

假设我们的目录下只有 `main.cpp` 一个文件，那么我们的 CMakeList.txt 可以这样写：

```cmake
cmake_minimum_required(VERSION 3.17)
project(test)
add_executable(test main.cpp)
```

<!-- more -->

这就是最简单的 CMakeList.txt 脚本，如果我们还有一个源文件 mymath.cpp 和 main.cpp 在同一目录下，那么，CMakeList.txt 可以写成这样：

```cmake
cmake_minimum_required(VERSION 3.17)
project(test)
add_executable(test test.cpp main.cpp)
```

就这么简单，其他更多内容可以 RTFM 或者 STFW，有很多例子可以供我们参考，如果我们对 C/C++ 文件的编译过程有很好的理解，这些例子足以帮我们了解全部内容。

我的 QC-LDPC 的 CMakeList.txt 如下：

```cmake
cmake_minimum_required(VERSION 3.17)
project(FFT_QSPA)
set(CMAKE_CXX_STANDARD 11)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(lib_math)
list(APPEND EXTRA_LIBS gfmath)

add_subdirectory(lib_ldpc)
list(APPEND EXTRA_LIBS lib_ldpc)

# add_executable(FFT_QSPA main.cpp)
# add_executable(FFT_QSPA fht.cpp)
add_executable(FFT_QSPA global_vars.cpp main.cpp)

target_link_libraries(FFT_QSPA PUBLIC ${EXTRA_LIBS})

target_include_directories(FFT_QSPA PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
```
