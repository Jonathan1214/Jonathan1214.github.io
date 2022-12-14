---
title: 『Effective-cpp』07 模板与泛型编程
copyright: true
notshow: false
date: 2022-09-12 15:55:54
updated:
categories:
  - [cpp]
  - [泛型编程]
tags:
---

## 41. 了解隐式接口和编译器多态

面向对象编程世界总是以**显示接口**和**运行期多态**解决问题。

Templates 中，**隐式接口**和编译器多态更加重要。

隐式接口，不基于函数签名式，而是由有效表达式组成。

<!-- more -->

## 42. 了解 typename 的双重意义

只是声明 template 的话，class 和 typename 没有区别。

一个简单的例子说明那个 typename 在 template 中的重要意义。

```cpp
template<typename C>
void print2nd(const C& container) {
    C::const_iterator* x;
}
```

现在问题出现了，`const_iterator` 是静态成员变量 还是 类型呢？这是有歧义的，需要使用 typename 加以说明，就像下面这样。

```cpp
template<typename C>
void print2nd(const C& container) {
    typename C::const_iterator* x;
}
```

即，typename 必须作为嵌套丛书类型名称的前缀词。

但是，typename 不可以出现在 base classes list 内的嵌套从属类型名称之前，也不可以在 member  initialization list 中作为 base class 修饰符。

显然，这个时候如果名称过长，我们应该考虑使用 typedef，如：

```cpp
template<typename IterT>
void workWithIterator(IterT iter) {
    typedef typename std::iterator_traits<IterT>:: value_type value_type;
    value_type tmep(*iter);
}
```

+ template 声明时，class 和 typename 相同
+ 使用关键字 typename 标识嵌套从属类型名称。

## 43. 学习处理模板化基类内的名称

偏特化版本：

```cpp
template<>
class MsgSender<CompanyZ> {
public:
    ...
    void sendSecret(const MsgInfo& info) { ... }
}
```

+ 可在 derived class templates 内通过 this-> 指涉 base class templates 内的成员名称，或者使用 using 直接点名。

## 44. 将与参数无关的代码抽离 templates

不要随意在 template 中增加参数，这会造成代码不必要的膨胀。

+ 因非类型模板参数（non-type template parameters）而造成的代码膨胀，往往可以消除，即以函数参数或class成员变量替换template参数。
+ 因类型参数而造成的代码膨胀，往往可降低，即让带有完全相同二进制表述（binary representations）的具现类型（instantiation types）共享实现码。

## 45. 运用成员函数模板接受所有兼容类型

。。。

TMP 等等
