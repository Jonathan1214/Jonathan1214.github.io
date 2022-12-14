---
title: 设计与声明
copyright: true
notshow: false
date: 2022-08-11 12:29:23
updated:
categories:
  - [cpp]
  - [effective]
tags:
  - cpp
---


18 让接口容易被正确使用，不易被误用

如果用户企图使用某个借口却没有获得他预期的行为，这个代码不该通过编译；如果代码通过了编译，它的作为就该是客户所想要的。

---

19 设计 class 犹如设计 type

20 宁以 `pass-by-reference-to-const` 替换 `pass-by-value`

21 必须返回对象时，别妄想返回其 `reference`

22 将成员变量声明为 private

23 宁以 `non-member`、`non-friennd` 替换 member 函数

24 若所有参数皆需类型转换，请为此采用 non-member 函数

25 考虑写出一个不抛出异常的 swap 函数
