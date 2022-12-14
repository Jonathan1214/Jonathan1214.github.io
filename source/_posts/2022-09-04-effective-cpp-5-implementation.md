---
title: effective-cpp-5-implementation
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


26 尽可能延后变量定义式的出现时间

27 尽量少做转型动作（Minimize casting）

28 避免返回 handles 指向对象内部成分

29 为 异常安全（exception-safe）努力是值得的

30 透彻了解 `inlining` 的里里外外

31 将文件间的编译依存关系降至最低

---

尽量延后变量定义式的出现，这样做可增加程序的清晰度并改善程序效率。

---

const_cast，将对象的常量性转除（cast away the constness）。

dynamic_cast

reinterpret_cast

static_cast，强迫隐式转换，将 non-cast 转为 cast，或则 int 转为 double。




