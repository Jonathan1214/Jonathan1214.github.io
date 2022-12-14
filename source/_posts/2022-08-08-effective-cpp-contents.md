---
title: 『effective』C++
copyright: true
notshow: false
date: 2022-08-08 23:51:49
updated:
categories:
  - cpp
tags:
  - cpp
---

Effective C++ 的目录。

## 1. 让自己习惯 C++

01 视 C++ 为一个语言联邦

02 尽量以 const, enum, inline 代替 #define

03 尽可能使用 const

04 确定对象被使用前已先被初始化

---

<!-- more -->

## 2. 构造/析构/赋值运算

05 了解 C++ 默默编写并调用哪些函数

06 若不想使用编译器自动生成的函数，就该明确拒绝

07 为多态基类声明 virtual 析构函数

08 别让异常逃离析构函数

09 绝不在构造和析构过程中调用 virtual 函数

10 令 operator= 返回一个 `reference to *this`

11 在 operator= 中处理 自我赋值

12 赋值对象时勿忘其每一个成分

---

## 3. 资源管理

13 以对象管理资源

14 在资源管理类中小心 copying 行为

15 在资源管理类中提供对原始资源的访问

16 成对使用 new 和 delete 时要采取相同的形式

17 以独立语句将 newed 对象置入智能指针

## 4. 设计与声明

18 让接口容易被正确使用，不易被误用

19 设计 class 犹如设计 type

20 宁以 `pass-by-reference-to-const` 替换 `pass-by-value`

21 必须返回对象时，别妄想返回其 `reference`

22 将成员变量声明为 private

23 宁以 `non-member`、`non-friennd` 替换 member 函数

24 若所有参数皆需类型转换，请为此采用 non-member 函数

25 考虑写出一个不抛出异常的 swap 函数

## 5. 实现

26 尽可能延后变量定义式的出现时间

27 尽量少做转型动作（Minimize casting）

28 避免返回 handles 指向对象内部成分

29 为 异常安全（exception-safe）努力是值得的

30 透彻了解 `inlining` 的里里外外

31 将文件间的编译依存关系降至最低

## 6. 继承与面向对象设计

32 确定你的 public 继承塑模出 `Is-a` 关系

33 避免遮掩继承而来的名称

34 区分接口继承和实现继承

35 考虑 virtual 函数以外的其他选择

36 绝不重新定义继承而来的 non-virtual 函数

37 绝不重新定义继承而来的缺省参数值

38 通过复合塑模出 `has-a` 或 `is-implemented-in-terms-of`

39 明智而审慎地使用 private 继承

40 明智而审慎地使用 多重继承

## 7. 模板与泛型编程

41 了解隐式接口和编译器多态

42 了解 typename 的双重含义

43 学习处理模板化基类内的名称

44 将参数无关的代码抽离 templates

45 运用 成员函数模板 接受所有兼容类型

46 需要类型转换时请为模板定义非成员函数

47 请使用 traits classes 表现类型信息

48 认识 template 元编程

## 8. 定制 new 和 delete

49 了解 new-handler 的行为

50 了解 new 和 delete 的合理替换时机

51 编写 new 和 delete 时需固守常规

52 写了 `placement new` 也要写 `placement delete`

## 9. 杂项讨论

53 不要轻忽编译器的警告

54 让自己熟悉包括 TR1 在内的标准程序库

55 让自己熟悉 Boost
