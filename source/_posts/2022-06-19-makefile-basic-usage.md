---
title: Makefile 的基本用法
copyright: 
notshow: false
date: 2022-06-19 16:17:53
updated:
categories:
tags:

- Makefile
- usage

---

Makefile 好，用过都说好，我们可以将一长串编译指令写到文件中，然后执行 make，就可以得到我们想要的结果。

简单来说，Makefile 的逻辑是这样的：

```makefile
target: dependency
    command
```

即：

```makefile
目标: 依赖
    命令
```

<!-- more -->

举个例子，假设当前目录下有文件 test.c：

```c
#include <stdio.h>
int main() {
    printf("hello world.\n");
    return 0;
}
```

编译该文件，我们会在 terminal 中输入 `gcc test.c -o test`，然后运行 `./test`就可以看到打印出来了 `hello world.`。按照上面的格式，我们可以写出 Makefile 的内容：

```makefile
test: test.c
    gcc test.c -o test
```

在 terminal 中执行 make，同样能够编译得到 test 文件，运行 `./test` 可以看到打印的 `hello world.`。

更进阶一点，编译多个文件，我们现在的源文件有两个 test.c 和 tools.c。内容分别如下：

```c
// test.c
#include <stdio.h>
#include "tools.h"
int main() {
    int a = 10, b = 9;
    printf("max val : %d", amx(a, b));
    printf("hello world.\n");
    return 0;
}
```

```c
#include "tools.h"

int amx(int a, int b) {
    return a > b ? a : b;
}
```

相应的头文件 tools.h 如下：

```c
int amx(int, int);
```

在 terminal 中使用 `gcc tools.c test.c -o test` 就可以完成编译任务，相应的 Makefile 内容如下：

```makefile
test: test.c tools.o
    gcc test.c tools.o -o test

tools.o: tools.c
    gcc -c tools.c
```

这就是我们需要的 Makefile 的全部内容。需要注意的是，Makefile 在被执行时，如果没有指定 target ，那么默认执行第一个 target，其他的 target 如果没有被选择执行的 target 直接依赖或者间接依赖，那么他们就不会被执行。因此，我们可以在上面的 Makefile 内加入删除中间文件 tools.o 的 target。

```makefile
test: test.c tools.o
    gcc test.c tools.o -o test

tools.o: tools.c
    gcc -c tools.c

clean:
    rm *.o
```

当然，我们也可以定义变量，使用变量时需要用上 `$(var_name)`，将编译器定义为一个变量使得我们在更换编译器的时候更加方便，也不会出错。

```makefile
CC = gcc

test: test.c tools.o
    $(CC) test.c tools.o -o test

tools.o: tools.c
    $(CC) -c tools.c

clean:
    rm *.o
```

以上就是全部内容，都是简单的例子，试一试就知道了，更复杂的内容可以 `RTFM` 以及 `STFW`。

参考连接：[[教程]Makefile的写法](https://www.bilibili.com/video/BV1Mx411m7fm)
