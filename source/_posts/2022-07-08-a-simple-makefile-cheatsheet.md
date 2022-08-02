---
title: 一份简单的 Makefile cheatsheet —— 关于 Makefile 多目录编译
copyright: true
notshow: false
date: 2022-07-08 19:44:28
updated:
categories:
  - 学习
tags:
  - Makefile
  - cheatsheet
  - gcc
---

如果还不知道最简单的 Makefile 应该怎么写，可以参考 [Makefile 基本用法](https://jonathan1214.github.io/2022/06/makefile-basic-usage/)。

参考链接：[多目录makefile](https://blog.csdn.net/guoxiaojie_415/article/details/52206139)。

简单的 Makefile 很好写，但是一旦复杂起来，尤其是多文件和多目录的 Makefile 就不是那么好写了。参考上面列出的文章，记录一个 cheatlist。

---

## 赋值

- = 是最基本的赋值
- := 是覆盖之前的值
- ?= 是如果没有被赋值过就赋予等号后面的值
- += 是添加等号后面的值

<!-- more -->

---

## example-1：分目录存放 src include

```makefile
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
OBJ_DIR=./obj

SRC=${wildcard ${SRC_DIR}/*.c}
OBJ=${patsubst %.c, $(OBJ_DIR)/%.o, ${notdir ${SRC}}}

#用于查看变量的值
#test:
#   echo $(SRC)
#   echo $(OBJ)

TARGET=main
BIN_TARGET=${BIN_DIR}/${TARGET}

CC=gcc
CFLAGS= -g -Wall -I${INC_DIR}

${BIN_TARGET}:${OBJ}
    ${CC} ${OBJ} -o $@

${OBJ_DIR}/%.o:${SRC_DIR}/%.c
    ${CC} ${CFLAGS} -c $< -o $@

clean:
    find ${OBJ_DIR} -name *.o -exec rm -rf {} \;
```

---

## example-2：分功能存放 sum add

```makfile
CC = g++
LD = g++
SUFFIX = .cpp
CUR_DIR = .
BIN_DIR = ./bin
DEC_DIR = $(CUR_DIR)/decoder
ENC_DIR = $(CUR_DIR)/encoder
LCC_DIR = $(CUR_DIR)/LDPCc

INC_DIR = -I$(LCC_DIR) \
            -I$(DEC_DIR) \
            -I$(ENC_DIR)

SRC =   $(wildcard $(LCC_DIR)/*$(SUFFIX)) \
        $(wildcard $(DEC_DIR)/*$(SUFFIX)) \
        $(wildcard $(ENC_DIR)/*$(SUFFIX)) \
        main.cpp

OBJ = $(patsubst %$(SUFFIX),%.o, $(SRC))
CLFAGS = -O3 $(INC_DIR)
TARGET = $(BIN_DIR)/ldpc

$(TARGET): $(OBJ)
    $(CC) $(OBJ) -o $@ --verbose -W
    @echo "Compile done."

$(OBJ):%.o:%$(SUFFIX)
    @echo "compiling $< --> $@"
    $(CC) $(CLFAGS) -c $< -o $@

all:
    @echo $(INC_DIR)
    @echo $(SRC)
    @echo $(OBJ)

clean:
    rm -f $(OBJ)
    @echo clean done
```

---

## 内嵌函数

例子中的 `wildcard` 和 `patsubst` 是 make 中的两个重要内嵌函数，如果不需要了解更多，那么可以直接参考上面的用法，否则 [STFW]()。

除此之外，make 中还有很多非常有意思的内嵌函数，列出如下，每一个的详细内容可以 [STFW]() 参考。

文本处理：

+ subst
+ patsubst
+ strip
+ findstring
+ filter
+ filter-out
+ sort
+ word
+ wordlist
+ words
+ firstword

文件名处理函数：

+ dir
+ notdir
+ suffix
+ basename
+ addsuffix
+ addprefix
+ join
+ wildcard

其他：

+ foreach
+ if
+ call
+ value
+ eval
+ origin
+ shell 函数
+ 控制函数
  + error
  + warning

---

## 静态模式

注意下面这一段，如果如要查找更加详细的内容，可以搜索 Makefile 的 **静态模式**。

```makefile
$(OBJ):%.o:%$(SUFFIX)
    @echo "compiling $< --> $@"
    $(CC) $(CLFAGS) -c $< -o $@
```

这是一种匹配的语法，

```
TARGETS ...: TARGET-PATTERN: PREREQ-PATTERNS ...
COMMANDS
```

如例子中所示的，`%.o` 中的 `%` 会匹配 `$(OBJ)`中的 `.o` 文件，得到文件名（假设匹配到了 `foo.o`，那么得到 `foo`），`foo` 和替换 `%.cpp` 中的 `%`，得到 `foo.cpp`，如此一来，展开后的 target 和 dependency 就变成了 `foo.o:foo.cpp`。command 部分的 `$<` 表示第一个依赖文件，`$@` 表示规则中的 target，详细可以参考 [Makefile 自动化变量]()。

举个更简单的例子：

```makefile
objects := foo.o bar.o

$(objects):%.o:%.c
    $(CC) -c $(CFLAGS) $< -o $@
```

第二段会扩展成如下：

```makefile
foo.o:foo.cpp
    $(CC) -c $(CFLAGS) foo.cpp -o foo.o
bar.o:bar.cpp
    $(CC) -c $(CFLAGS) bar.cpp -o bar.o
```

从上面这个例子，我们知道当有多个 objects，我们应该怎样写 Makefile，这可以作为 cheatsheet。

更进一步的，如果上面这个例子中，object 中不仅仅有 .o 文件，那么 make 会给一个失败提示，我们可以使用 filter 函数。搜索 [Makefile 内嵌函数]() 获得更多信息。

一个简单的例子如下：

```makefile
files = foo.elc bar.o lose.o
$(filter %.o,$(files)):%.o:%.c
    $(CC) -c $(CFLAGS) $< -o $@
$(filter %.elc,$(files)):%.elc:%.el
    emacs -f batch-byte-compile $<
```

---

更多内容可以参考：[gnumake manual](https://www.gnu.org/software/make/manual/)

当然，这么经典的工具的 Manual，也有很多翻译版可以参考。
