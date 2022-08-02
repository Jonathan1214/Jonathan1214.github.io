---
title: ch3-handling-multiple-clocks-The-art-of-hardware-architecture
copyright: true
notshow: true
tags:
  - TAHA
  - IC
  - CDC
date: 2022-03-25 10:21:57
updated:
categories:
---

单时钟设计（或者说是同步设计），在单时钟域中，有单个时钟贯穿整个设计，同多时钟设计相比，这样的设计更易于实现，并且更少产生与亚稳态、建立和保持时间违背方面的问题。

## 3.2 多时钟域

包含如下时钟关系之一的设计：

+ 时钟的频率不同
+ 时钟频率相同，但相位不同

![image-20220325102523304](D:\Documents\Jonathan1214.github.io\source\_drafts\ch3-handling-multiple-clocks-The-art-of-hardware-architecture\image-20220325102523304.png)

## 3.3 多时钟域设计的难题

面临下列问题：

+ 建立时间和保持时间的违背
+ 亚稳态

### 违背建立时间和保持时间

**建立时间**：在时钟脉冲到来前，输入数据需要保持稳定的时间。

**保持时间**：在时钟脉冲到达后，输入数据扔需要保持稳定的时间。

在多时钟域下，容易违背这两个条件，如下图所示：

![image-20220325102839053](D:\Documents\Jonathan1214.github.io\source\_drafts\ch3-handling-multiple-clocks-The-art-of-hardware-architecture\image-20220325102839053.png)

## 3.4 多时钟设计的处理技术

通用的准则：

+ 时钟命名规则
+ 分模块设计

所谓时钟命名规则，就是信号名中需要带有其所属时钟域的信息。如，系统时钟可以命名为 sys_clk，发送时钟命名为 tx_clk，系统时钟驱动的信号，可以用类似 sys_rom_addr 这样的方式作为名字。之所以这么做，是为了易于分辨。

### 分模块设计

+ 每个模块只应当在单个时钟下工作
+ 在信号跨时钟域传输时，使用同步器模块，使得所有信号进入某个时钟域内的模块时，与该模块的时钟保持同步。
+ 同步器模块的规模应尽可能小

### 跨时钟域

两类信号：

+ 控制信号
+ 数据信号

控制信号跨时钟域传输时，**需要使用多级同步器以降低亚稳态出现的概率，但是会增加电路的延时。**

![image-20220325104047078](D:\Documents\Jonathan1214.github.io\source\_drafts\ch3-handling-multiple-clocks-The-art-of-hardware-architecture\image-20220325104047078.png)

一般来讲，使用两级同步器即可，只有在时钟频率非常高的设计中才要求使用三级同步器。

保证数据信号正确传输的方法：

+ 使用握手信号
+ 使用异步 FIFO

> 控制信号和数据信号的区别就在于信号的宽度，控制信号一般是 1bit，而数据信号是多比特的，多比特信号简单使用寄存器打拍的方式同步。

## 3.5 跨时钟域

这里涵盖的是 **跨同步时钟域** 的问题：

+ 同频零相位差时钟
+ 同频恒定相位差时钟
+ 非同频可变相位差时钟
  + 整数倍时钟
  + 有理数倍时钟

## 3.6 握手信号方法

![image-20220326090836705](D:\Documents\Jonathan1214.github.io\source\_drafts\ch3-handling-multiple-clocks-The-art-of-hardware-architecture\image-20220326090836705.png)

要求：

+ 数据应该在发送时钟域内稳定至少两个时钟上升沿。
+ 请求信号 xreq 的宽度应该超过两个上升沿时钟，否则从告诉时钟域向低速时钟域传递可能无法捕捉到该信号。

缺点：延迟太大。

## 3.7 使用同步 FIFO 传输数据

![image-20220326091114307](D:\Documents\Jonathan1214.github.io\source\_drafts\ch3-handling-multiple-clocks-The-art-of-hardware-architecture\image-20220326091114307.png)

核心是判断空满，一种方法是扩大位宽，另一种方法是直接判断空满：

+ full：`wr_fifo && (rd_ptr == wr_ptr + 1'b1)`
+ empty：`rd_fifo && (rw_ptr == rd_ptr + 1'b1)`

## 3.7 异步 FIFO

![image-20220326100924782](D:\Documents\Jonathan1214.github.io\source\_drafts\ch3-handling-multiple-clocks-The-art-of-hardware-architecture\image-20220326100924782.png)

FIFO 用于对性能要求较高的设计中，尤其是时钟延迟比系统资源更为重要的环境中。

为什么要使用格雷码？格雷码下相邻地址信号只有 1bit 差距，因此，可以看作是异步的单比特信号。

![image-20220326104345632](D:\Documents\Jonathan1214.github.io\source\_drafts\ch3-handling-multiple-clocks-The-art-of-hardware-architecture\image-20220326104345632.png)

使用格雷码直接判断空满情况，而不需要转换到二进制码。
