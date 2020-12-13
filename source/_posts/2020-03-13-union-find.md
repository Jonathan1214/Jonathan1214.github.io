---
title: union-find算法的原理及实现
date: 2020-03-13 15:26:53
updated:
categories:
  - 学习
tags:
  - 算法
  - union-find
  - Java
mathjax: true
---
在计算机网络中，对于任意两个节点，可以在其间构建一条连接建立通信，这样做没有问题，但是在整个网络中都这么做会导致需要建立的连接非常多，容易计算得到`N`个节点的网络需要的连接数`N(N-1)/2`，这增加了网络的负担，实现起来也不容易，有什么办法改进呢？六度空间理论大家都知道，说的是最多通过六个人，我们可以和世界上任何人建立联系，那么如何知道两个人之间是否可以建立联系呢？这两个问题其实都属于连通性问题，可以使用`union-find`算法解决，步骤如下：

## 1. 数据准备

`p`和`q`表示两个抽象的节点，可以用整数表示，如果『p，q 是相连的』，则意味着：

+ 自反性：`p`和`p`是相连的。
+ 对称性：如果`p`和`q`相连，则`q`和`p`也是相连的。
+ 传递性：如果`p`和`q`相连，`q`和`r`相连，则`p`和`r`也相连。

我们可以用一个数组表示所有的节点，数组的每个位置表示一个节点，每个位置的值表示这个节点所在分量的标识符，初始化的时候每个节点的标识符都是其本身，如下所示：
<!--more-->

```Java
void UF(int N) {
    a = new int[N]; // 初始化节点数组
    for (int i = 0; i < N; i++)
        a[i] = i;
}
```

## 2. 实现

### quick-find

在`union-find`算法中，有两个目标需要实现：判断两个节点是否连通和连接两个节点的。一种简单的思路是这样的，规定同属一个连通分量的标识符相同，比如：节点`0`，`1`和`2`是连通的，我们选择`1`为标识符，那么`a[0]=a[1]=a[2]=1`。这样做判断两个节点是否连通就可以在常数时间完成，基于此规则我们可以实现`quick-find`算法，但是这样做`union`的成本就会上升，每次`union`，需要遍历所有的节点，并对合适节点的标识符进行改变，这是个平方级别的算法，如下所示。

```Java
boolean isConnected(int p, int q) {
  return find(p)==find(q);
}
int find(int p) { return a[p]; }
void union(int p, int q) {
    int pp = find(p);   // p 节点的标识符
    int qq = find(q);   // q 节点的标识符
    if (pp == qq) return;
    // 将 pp 标识符全部改成 qq
    for (int i = 0; i < a.length; i++)
        if (a[i] == pp) a[i] = qq;
}
```

### quick-union

quick-find算法中，union的成本是平方级别的，其原因在于每次union需要遍历全部的节点，可以进行一些调整，得到改进，这就是quick-union算法。具体实现：在同一类别的中的节点，我们不再让所有节点保存相同的标识符，而是在节点中保持其父节点，类似一棵树，不过是向上走的，子节点指向父节点，根节点保存的是他自己，这样一来，进行union操作时，至于遍历找到根节点，然后让其中一个根节点指向另一个根节点即可，进行find操作时，只需遍历找到根节点即指向自身的节点。

```Java
int find(int p) {
    while (a[p] != p) p = a[p];
    return p;
}
void union(int p, int q) {
    int pRoot = find(p);
    int qRoot = find(q);
    // pRoot 节点指向 Qroot
    a[pRoot] = qRoot;
}
```

### 加权 quick-union

这样做没什么问题，但是在最坏情况下，节点是依次相连的，串成一串，这会导致算法的性能下降，我们对其稍加改进，每次union时，都把节点数小的那一组连接到节点数大的那一组，这就是加权的quick-union算法。实现这个算法我们需要一个数组保存每个节点下节点的数目，对根节点而言，这个数就是它所在组的大小。

```Java
UF(int N) {
    a = new int[N];     // 初始化节点数组
    sz = new int[N];    // 保存节点数目
    for (int i = 0; i < N; i++)
        a[i] = i;
    for (int i = 0; i < N; i++)
        sz[i] = 1;
}
// find 算法没有改变
void union(int p, int q) {
    int pRoot = find(p);
    int qRoot = find(q);
    if (pRoot == qRoot) return;
    if (sz[pRoot] > sz[qRoot]) { // p 所在组较大
        a[qRoot] = pRoot; // 将q连接到q上
        sz[pRoot] += sz[qRoot]; // 更新 pRoot 下的节点数
    } else {    // q 所在组较大
        a[pRoot] = qRoot;
        sz[qRoot] += sz[pRoot];
    }
}
```

### 路径压缩

还有一种路径压缩算法可以改进quick-union，即每次查找时，都把途径的节点指向根节点，这样均摊下来的find成本比较小，可以证明，路径压缩的加权quick-union算法是实现union-find最快的算法。

```Java
int find(int p) {
    int x = p, t;
    while (a[p] != p) p = a[p]; // 找到根节点
    while (x != p) { // 直到到达根节点
        t = a[x];   // 保存当前节点的父节点
        a[x] = p;   // 当前节点直接连接到根节点
        x = t;      // 移动到当前节点的父节点
    }
}
// union 算法不变
```

---
回到开头的那两个问题，有了union-find算法，我们来尝试解决它们。对于网络中节点是否需要构建新的连接，抽象出网络的节点构建起`UF`后，执行`isConnected()`即可判断是否需要建立新的连接，对于两个人是否可以建立连接的问题，我们用同样的方法也可以解决，但要是想通过最少的中间人就认识一个人，该怎么做呢，这又是另外一个问题了。
