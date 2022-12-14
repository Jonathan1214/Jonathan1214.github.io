---
title: 『Effective cpp』06 继承与面向对象设计
copyright: true
notshow: false
date: 2022-09-12 13:48:11
updated:
categories:
  - [cpp]
  - [oop]
tags:
  - cpp
  - oop
---

## 32. 确定 public 继承塑模出 is-a 关系

+ public 继承意味 is-a。适用于 base classes 身上的每一件事情一定也适用于 derived classes身上，因为每一个 derived class对象也都是一个 base class 对象。

<!-- more -->

## 33. 避免遮掩继承而来的名称

+ derived classes 内的名称会遮掩 base classes 内的名称。在 public 继承下从来没有人希望如此。
+ 为了让遮掩的名称再见天日，可使用 using 声明式或转交函数（forwarding functions）。

## 34. 区分接口继承和实现继承

成员函数的接口总是被继承。

声明一个 pure virtual 函数的目的是为了让 derived classes 只继承函数接口。

声明 impure virtual 函数，是让derived classes **继承该函数的接口和缺省实现**。

声明 non-virtual 函数的目的是令 derived classes 继承函数的接口及一份强制性实现。

+ pure vitual 函数
+ impure virtual 函数
+ non-virtual 函数

take-away message

+ 接口继承和实现继承不同。在 public 继承下，derived classes 总是继承 base class 的接口
+ pure virtual 函数只具体指定接口继承
+ impure virtual 函数具体指定接口继承及缺省实现继承
+ non-virual 函数具体指定接口继承及强制性实现继承。

---

## 36. 绝不重新定义继承而来的 non-virtual 函数

non-virtual 函数是静态绑定的。

virtual 函数是动态绑定的。

## 37. 绝不重新定义继承而来的缺省参数值

virtual 函数系动态绑定，而缺省参数值却是静态绑定的。

静态绑定又名前期绑定（early binding），动态绑定又名后期绑定（late，binding）。

静态类型（static type），就是它在程序中被声明时所采用的类型。

动态类型是指目前所指对象的类型。动态类型可以表现出一个对象将会有什么行为。

virtual 函数系动态绑定而来，即调用 virtual 函数时，究竟调用哪一份函数实现代码，取决于发出调用的那个对象的动态类型。

```cpp
class Shape {
public:
    enum ShapeColor {Red, Green, Blue};
    void draw(ShapeColor color = Red) const {
        doDraw(color);
    }
    ...
private:
    virtual void doDraw(ShapeColor color) const = 0;
};

class Rectangle: public Shape {
public:
    ...
private:
    virtual void doDraw(ShapeColor color) const; // 不需指定缺省参数值
}
```

+ 绝对不要重新定义一个继承而来的缺省参数值，因为缺省参数值都是静态绑定的，而 virtual 函数——你唯一应该覆写的东西，却是动态绑定的。

## 38. 通过复合塑模出 has-a 或根据某物实现出

+ 复合的意义与 public 继承完全不同。
+ 在应用域，复合意味 has-a。在实现域，复合意味着 is-implemented-in-terms-of。

## 39. 明智而审慎使用 private 继承

private 继承带来的结果：

+ is-a 关系不会自动存在
+ 继承而来的所有成员，均变为 private

这意味着，implemented-in-terms-of。

也就是，private 意味着只有实现部分被继承，接口部分应略去。

如果 D 以 private 方式继承 B，意思是 D 对象根据 B 对象实现而得。

private 继承在软件设计层面没有意义，其意义只在于软件实现层面。

这显然和复合有重复，如何选择？尽可能使用复合，而非 private 继承。

当 proteced 成员和/或virtual函数牵扯进来时，需要考虑 private 继承。

+ private 可以造成 empty base 最优化，在某些空间优先的场景下有使用。

## 40. 明智而审慎使用多重继承

多重继承会造成钻石继承。

使用 virtual 继承避免这种情况，但需要付出访问时间的代价等等。

+ 多重继承比单一继承复杂，它可能导致新的歧义性，以及对 virtual 继承的需要。
+ virtual 继承会增加大小、速度、初始化复杂度等等成本。如果 virtual base classes 不带任何数据，将是最具使用价值的情况。
+ 多重继承确有正当用途。其中一个情节涉及 public 继承某个 Interface class 和 private 继承某个协助实现的 class 的两相结合。



