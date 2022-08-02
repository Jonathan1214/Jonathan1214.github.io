---
title: 『TAHA』02 时钟和复位
copyright: true
notshow: true
tags:
  - TAHA
  - Verilog
  - IC
date: 2022-03-23 20:35:10
updated:
categories:
---

## 同步设计

**何为同步设计？**在同步设计中，由单个主时钟和单个主置位、复位信号驱动设计中所有的时序器件。

经验表明，对 ASIC 时序控制最安全的方法就是同步设计。

同步设计避坑指南：

+ 避免使用行波计数器
+ 门控时钟
+ 双边沿或混合边沿时钟
+ 用触发器驱动另一个触发器的异步复位端

推荐的设计技术：

+ 避免在设计中出现组合环路
+ 避免数字设计中的延迟链
+ 避免使用异步脉冲产生器
+ 避免使用锁存器
+ 避免使用双沿时钟

## 时钟方案

避免在内部产生时钟

时钟分频可以使用同步计数器而不是行波计数器

小心使用多路时钟

小心使用门控时钟

## 门控时钟方法学

使用门控时钟主要是为了降低功耗。

在同步设计中，系统时钟连接到每个寄存器的时钟端，这使得功耗主要由三部分组成：

+ 时钟沿变化的组合逻辑产生的功耗
+ 触发器产生的功耗
+ 设计中时钟树产生的功耗

门控时钟可以存在于时钟树的根部、末端，或者两者之间的任何位置。

![image-20220323223559804](D:\Documents\Jonathan1214.github.io\source\_drafts\ch2-clock-and-reset-of-The-art-of-hardware-architecture\image-20220323223559804.png)

## 复位信号的设计策略

最好的方法，注意在这种情况下，第二个触发器不会出现恢复时间亚稳态问题，因为在移除复位时该触发器的输入和输出都为低电平。

![image-20220323225848060](D:\Documents\Jonathan1214.github.io\source\_drafts\ch2-clock-and-reset-of-The-art-of-hardware-architecture\image-20220323225848060.png)

## 控制时钟偏移

对于同一时钟边沿偏移较大的寄存器，如果舒徐相邻，那么在向其提供时钟时，就会有违背时序的潜在风险。

![image-20220323230645958](D:\Documents\Jonathan1214.github.io\source\_drafts\ch2-clock-and-reset-of-The-art-of-hardware-architecture\image-20220323230645958.png)

如上图所示，两个触发器之间的时钟偏移定义为：

$$T_{skew_{i,j}}=T_{c_i}-T_{c_j}$$

这里 $$T_{c_i}$$ 和 $$T_{c_j}$$ 分别是从时钟源到触发器 $$F_i$$ 和 $$F_j$$ 的延迟。

时钟偏移并不都是有害的，其实会帮助我们的建立时间，但是时钟偏移过大也会导致保持时间问题，即出现短路径问题。
