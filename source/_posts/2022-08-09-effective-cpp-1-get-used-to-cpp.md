---
title: 让自己习惯cpp
copyright: true
notshow: false
date: 2022-08-09 20:48:53
updated:
categories:
  - [cpp]
  - [effective]
tags:
  - cpp
  - effective
---

### 视 C++ 为一个语言联邦

### 尽量以 const, enum, inline 代替 #define

+ 对于单纯常量，最好以 const 对象或 enums 替换 #define
+ 对于形似函数的宏，最好改用 inline 函数替换 #define

### 尽可能使用 const

const 允许我们指定一个 语义约束，编译器会强制实施这项约束。

const 可修饰常量 及 static 对象。
可修改 classes 内部的 static 或 non-static 成员变量。

<!-- more -->

面对指针，我们也可以指定指针自身、指针所指事物或两者都是 const。


```cpp
char greeting[] = "hello";
char *p = greeting; // non, non
const char *p = greeting; // non-const pointer, const data
char* const p = greeting; // const pointer, non-const data
const char* const p = greeting; // const, const
```

简单关于 const 和指针的技巧：const 出现在星号左边，表示被指物是常量，如果在右侧，表示指针是常量。

令函数返回 const 值，有很好的保护作用。

#### const 成员函数

+ 确认该成员函数可作用于 const 对象
+ 使 class 接口更容易被理解
+ 使操作 const 对象成为可能
+ **两个成员函数如果只是 constness 不同，则可以被重载**

为何对象需要定义 const 成员函数？

真实的 const 对象大多用于 pass-by-pointer-to-const 或 passed-by-reference-to-const 的传递结果。

```cpp
void print(const TextBlock& ctb) { // ctb is a const
    // do something
}
```

---

改变函数的返回值可行吗？尤其是重载运算符。

```cpp
tb[0] = 'x';
```

如果我们想这样做，那么 `operator[]` 需要返回一个 `char&`。

---

成员函数是 const 意味着什么？

bitwise constness 和 logical constness

bitwise constness 认为 const 不该改变对象中的任何内容。const 成员不可以更改对象内任何 non-static 成员变量。

看一个 logical constness 的例子：

```cpp
class CTextBlock {
public:
    ...
    char& operator[](std::size_t position) const
    { return pText[position]; }
private:
    char* pText;
};

const CTextBlock cctb("Hello");
char* pc = &cctb[0];
*pc = 'J'
```

我们成功该变了一个 const 对象，当然，只是改变其指针成员变量指向的内容。

如果我们确实想在 const 成员函数里修改成员变量，可以将变量声明为 mutable 类型，这将释放掉 non-static 成员变量的 bitwise constness 约束。

```cpp
class CTextBlock {
public:
    std::size_t length() const;s
private:
    char *pText;
    mutable std::size_t textLength;
    mutable bool lengthIsValid;
};
```

---

#### 在 const 和 non-const 成员函数中避免重复

使用 const 版本的成员函数实现 non-const 成员函数。

```cpp
class TextBlock {
public:
    const char& operator[](std::size_t position) const 
    { ...
      ...
      return text[position];
    }
    char& operator[](std::size_t position)
    {
        return const_cast<char&>(
            static_cast<const TextBlock&>(*this)[position];
        );
    }
};
```

在此，我们终于看到了 const_cast 的作用了。

> const 是一个奇妙且非比寻常的东西。
> 
> + 指针和迭代器上
> + 在指针、迭代器及 reference 指涉的对象身上
> + 在函数参数和返回类型身上
> + 在local 变量上
> + 在成员函数上

#### note

+ 将某些东西声明为 const 可帮助编译器侦测出错误用法。const 可被施加于任何作用域内的对象、函数参数、函数返回类型、成员函数本体。
+ 编译器强制实施 bitwise constness，但你编写程序时应该使用 “概念上的常量性” conceptual constness。
+ 当 const 和 non-const 成员函数有着实质等价的实现时，令 non-const 版本调用 const 本本可避免代码重复。

### 确定对象被使用前已先被初始化

永远在使用对象之前，先将它初始化。

在构造函数中，使用 member initialization list 特性。

在这个 list 中，会依次执行 copy assignment。

成员初始化顺序：先 base 后 derived，成员变量按照声明顺序进行，而不是 list 中的顺序。

最后需要关心的事情：**不同编译单元内定义的 non-local static 对象 的初始化顺序**。

函数内的 static 对象被称为 local static 对象，其他的是 non-static 对象。

static 对象在 main() 结束时被自动调用。

**C++ 对于定义于不同编译单元内的 non-local static 对象的初始化相对次序并无明确定义。**

为了解决这个问题，我们可以使用一个小小的设计：**将每个 non-local static 对象搬到自己专属函数内（该对象在此函数内被声明为 static）**。这些函数返回一个 reference 指向它所含的对象。用户调用这些函数，而不直接指涉这些对象。

即用 local static 对象 替换 non-local static。这其实就是 Singleton 模式的常见实现手法。

```cpp
class FileSystem { ... };
FileSystem& tfs() {
    static FileSystem fs;
    return fs;
}
class Directory { ... };
Directory::Directory(params) {
    ...
    std::size_t disks = tfs().numDisks();
    ...
}
Directory& tmpDir() {
    static Directory td;
    return td;
}
```

在这里我们返回 static 临时变量，很有意思。这保证了我们的变量是一定存在的。

总结一下：

+ 手工初始化内置型 non-member 对象
+ 使用 member initialization lists 对付对象的所有成分。
+ 以 local static 对象替换 non-local static 对象

