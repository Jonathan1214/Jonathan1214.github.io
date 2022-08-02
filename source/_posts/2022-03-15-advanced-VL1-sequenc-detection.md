---
title: 输入序列连续的序列检测
copyright: true
notshow: false
date: 2022-03-15 09:30:01
updated:
categories:
 - 学习
 - IC
tags:
  - Verilog
  - IC设计
  - 序列检测
---

这段时间在准备暑期实习，刚好牛客上新开放了 Verilog 刷题的模块，大概是为了这波风口，大家都在一起疯狂。

[输入序列连续的序列检测](https://www.nowcoder.com/practice/d65c2204fae944d2a6d9a3b32aa37b39?tpId=302&tqId=5000628&ru=/exam/oj&qru=/ta/verilog-advanced/question-ranking&sourceUrl=%2Fexam%2Foj%3Ftab%3DVerilog%25E7%25AF%2587%26topicId%3D302)

序列检测算是比较简单的题了，无非两种方法，移位寄存然后判断，或者更复杂一点的用状态机实现，序列检测还可以分为可重复检测和非可重复检测，具体实现上有细微的差别，都不算复杂。
