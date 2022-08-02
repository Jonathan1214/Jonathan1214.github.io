---
title: ch5-low-power-design-The-Art-of-Hardware-Architecture
copyright: true
notshow: true
tags:
  - IC
  - TAHA
  - 低功耗
date: 2022-03-30 11:02:55
updated:
categories:
---

## 功耗源

+ 浪涌：启动时产生的电流相关。
+ 静态功耗：待机功耗，漏电流
+ 动态功耗：开关功耗或者逻辑转换所引起的功耗。

$$
P_{dynamic} = SC_LV_{dd^2}f_{clk}
$$

动态功耗占主要地位，80%为典型值。
