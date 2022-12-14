---
title: 资源管理
copyright: true
notshow: true
date: 2022-08-11 09:08:25
updated:
categories:
  - [cpp]
  - [effective]
tags:
  - cpp
---

## 以对象管理资源

一个简单易懂且基于对象（object-based）的资源管理办法，建立在 C++ 对构造函数、析构函数、copying 函数的基础上。

```cpp
Investment* createInvestment();

void f() {
    Investment* pInv = createInvestment();
    ...
    delete pInv;
    // 这是不安全的
}
```

<!-- more -->

把资源（指针）放进对象内，便可倚赖 C++ 的 析构函数自动调用机制 确保资源被释放。

STL 提供 auto_ptr 正是针对这种情况设计的的。其析构函数自动对其所指对象调用 delete。

```cpp
void f() {
    std::auto_ptr<Investment> pInv(createInvestment());
    ...
}
```

+ 获得资源后立即放进管理对象：Resource Acquisition Is Initialization, RAII
+ 管理对象 运用析构函数确保资源被释放

auto_ptr 的不寻常的性质：**若通过 copy 构造函数或 copy assignment 操作符复制它们，它们会变成 null，而复制的指针取得资源的唯一拥有权。** 即，auto_ptr 管理的资源只能受到一个 auto_ptr 的管理，不允许复制，这当然保证了绝对的安全，但某些时候我们想要正常的复制行为。

替代方案就是 引用计数型智慧指针（reference-counting smart pointer, RCSP）。shared_ptr 就是个 RCSP。其用法与 auto_ptr 并无区别，只是它的复制显得正常许多。

注意，上面提到的两种资源管理类，在析构时执行的是 delete，而非 delete []。

### Note

+ 防止资源泄漏，请使用 RAII 对象，它们在构造函数中获得资源并在析构函数中释放资源。
+ 常用的 RAII classes 是 shared_ptr 和 auto_ptr。前者通常更好，因为其 copy 行为直观。注意 auto_ptr 的复制动作带来额外效果。

---

## 在资源管理类中小心 copying 行为

有时，我们需要自定义 RAII 对象，这时候就要决定 copying 时会发生什么。

+ 禁止复制，copying 函数声明为 private 即可。
+ 对底层资源使用 引用计数法（refrence-count），shared_ptr
+ 复制底部资源，deap copying
+ 转移底部资源控制权，auto_ptr

### Note

+ 复制 RAII 对象必须一并复制它所管理的资源，所以资源的 copying 行为决定了 RAII 对象的 copying 行为。
+ 普遍而常见的 RAII class copying 行为是：抑制 copying、施行引用计数法（refrence counting）。不过其他行为也可。

---

## 在资源管理类中提供对原始资源的访问

auto_ptr 和 shared_ptr 均提供了 get() 来获得原始资源的指针。

---

## 成对使用 new 和 delete 时要采取相同的形式

```cpp
delete ptr;
delete [] aptr;
```

一定要匹配上，具体为何，如果了解动态内存分配，就不会再有疑惑了，因为数组指针和普通指针，记录的信息是不同的，delete 和 delete [] 对指针的解释不同，也就意味着不同类型的析构。

---

## 以独立语句将 newed 对象置入智能指针

Store newed objects in smart pointers in standalone statements.

+ 以独立语句将 newed 对象存储于（置入）智能指针内。如果不这样做，一旦异常被抛出，有可能导致难以察觉的资源泄漏。


