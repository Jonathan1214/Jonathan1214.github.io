---
title: 构造/析构/赋值运算
copyright: true
notshow: false
date: 2022-08-10 23:24:41
updated:
categories:
  - [cpp]
  - [effectvie]
tags:
  - cpp
---

### 了解 C++ 默默编写并调用哪些函数

+ copy 构造函数
+ copy assignment 操作符
+ 析构函数
+ default 构造函数

这些函数都是 public 且 inline 的。

<!-- more -->

如果 成员变量 中有引用（指针）和 const 变量，通常我们需要主动编写 copy assignment。

### 若不想使用编译器自动生成的函数，就该明确拒绝

即，我不想对象被拷贝，应该怎么做才能拒绝生成默认的 copy 函数。

这是一个小技巧：将 copy 构造和 assignment 运算符声明为 pirvate 即可，而且我们不用实现他们。这样一来，如果有人调用他们，就会获得 linkage error。

我们还可以把 linkage error 提前到 编译期 发生。

```cpp
class Uncopyable {
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&); // 阻止 copying
    Uncopyable& operator=(const Uncopyable&);
};

class HomeForSale: private Uncopyable {
    // 不用再声明 copy 构造和 copy assign 操作符
};
```

#### Note

为了禁止编译器自动提供的机能，可将相应的成员函数声明为 private 并且不实现它。

---

### 为多态基类声明 virtual 析构函数

> 当 derived class 对象经由一个 base class 指针被删除，而该 base class 带着一个 non-virtual 析构函数，其结果是未定义的。

通常在这种情况下，base class 的部分会被析构掉，但 derived class 的部分不会发生改变。

解决办法是，为 base class 声明 virtual 析构函数。

但是，virtual 析构函数也不该被滥用，即 class 中如果没有其他 virtual 函数，我们就不需要也不应该声明 virtual 析构函数。这是因为 virtual 函数是通过 vptr（virtual table pointer）实现的，这会导致 class 所占用的空间变大，且不利于移植。

小心继承类，如果 base class 没有 virtual 析构，很可能会发生一些奇怪的错误。

pure virtual 函数为我声明了一个 abstract classes，即不能被实例化（instantiated）的 class。

---

#### Note

+ polymorphic（带多态性质）的 base classes 应该声明一个 virtual 析构函数。如果 class 带有任何 virtual 函数，它就应该拥有一个 virtual 析构函数。
+ Classes 的设计目的如果不是作为 base classes 使用，或不是为了具备多态性，就不该声明 virtual 析构函数。

---

### 别让异常逃离析构函数

C++ 并不禁止析构函数吐出异常，但并不鼓励这么做。我们应该在 virtual 中就把异常处理掉。

考虑下面这个例子：

```cpp
class Widget {
    ...
    ~Widget() { ... } // 假设可能吐出异常
};
void dosomething() {
    std::vector<Widge> v;
    ...  // 销毁 v
}
```

一旦 Widget 吐出异常，vector 中后续的析构无法继续进行。这会导致恶劣的行为。

#### Note

+ 析构函数绝对不要吐出异常。
+ 如果客户需要对某个操作函数运行期间抛出的异常做出反应，那么 class 应该提供一个普通函数（而非在析构函数中）执行该操作。

---

### 绝不在构造和析构过程中调用 virtual 函数

base class 构造期间 virtual 函数绝不会下降到 derived classed 阶层。

> base class 构造期间，virtual 函数不是 virtual 函数。

#### Note

+ 在构造和析构期间不要调用 virtual 函数，因为这类调用从不下降至 derived class。

---

### 令 operator= 返回一个 `reference to *this`

有趣的连续赋值形式：

```cpp
int x, y, z;;
x = y = z = 15;
```

这暗示着，赋值采用右结合律。即 `x = (y = (z = 15));`。

扩展到对象中，这意味着 `operator=` 需要返回一个 `referece` 指向操作符左侧的实参。看下面的例子：

```cpp
class Widget {
public:
    ...
    Widget& operator=(const Widget& rhs) {
        ...
        return *this; // 返回左侧对象
    }
};
```

所有和赋值相关的运算都应该返回这样的值，如 `+=`、`*=`等等。

#### Note

+ 令 assignment 操作符返回一个 refrence to *this

---

### 在 operator= 中处理 自我赋值

一定要考虑自我赋值：`A = A;` 的情况。

危险往往发生在 class 中有指针时，copy assginment 通常意味着指针的释放和新内容的开辟。这会导致问题。

```cpp
Widget& Widget::operator=(const Widget& rhs) {
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}
```

如果 `*this` 和 `rhs` 是同一对象，那么就会导致 deference nullptr 的问题。

做一个 identity test 即可避免这种问题：

```cpp
Widget& Widget::operator=(const Widget& rhs) {
    if (this == &rhs) return *this; // identity test

    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}
```

#### 巧妙语句顺序

```cpp
Wiget& Widget::operator=(const Widget& rhs) {
    Bitmap* pOrig = pb;
    pb = new Bitmap(*rhs.pb);
    delete pOrig;
    return *this;
}
```

#### 使用 copy and swap 技术

```cpp
class Widget {
    ...
    void swap(Widget& rhs);
    ...
};
Widget& Widget::operator=(const Widget& rhs) {
    Widget temp(rhs);  // 为 rhs 数据制作副本
    swap(temp);        // 交换
    return *this;
}
// 另一个版本
Widget& Widget::operator=(Widget rhs) {
    swap(rhs);        // 交换
    return *this;
}
```

#### Note

+ 确保当对象自我赋值时 operator= 有良好行为。
+ 确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确。

---

### 赋值对象时勿忘其每一个成分

编写 derived class 的 copying 函数时，要小心操作，base class 的变量需要调用他们的 copying 函数完成复制。

+ Copying 函数应该确保复制 “对象内所有成员变量” 及 “所有 base class 成分”。
+ 不要尝试以某个 copying 函数实现另一个 copying 函数。应该将共同机能放进第三个函数中。

