---
title: 算法笔记 —— 图
categories:
  - 学习
tags:
  - 数据结构
  - 算法
  - Java
  - notes
toc: true
date: 2020-04-10 11:03:42
updated:
---

在许多计算机应用中，由相连的结点所表示的模型起到了关键的作用。这些结点之间的连接很自然地会让人们产生一连串的疑问：沿着这些连接能否从一个结点到达另一个结点？有多少个结点和指定的结点相连？两个结点之间最短的连接是哪一条？要描述这些问题，我们要使用一种抽象的数学对象，叫做图。
<!-- more -->

## 1. 无向图

*无向图的定义*：无向图是由一组顶点和一组能够将两个顶点相连的边组成的。在无向图中，边（edge）仅仅是两个顶点（vertex）间的连接。根据这个定义，顶点叫什么名字无关紧要，我们使用 0 到 V-1 来表示一张含有 V 个顶点的图中的各个顶点，这样的表示便于使用数组的索引来访问各个结点，我们可以直接用数组的索引作为结点的名称，事实上如果顶点不符合我们的预设，我们也可以把它们映射到 0 到 V-1 上来。

在这个定义下，允许出现下面两种特殊情况：

+ 自环：即一条连接一个顶点和其自身的边；
+ 连接同一对顶点的两条边称为平行边。

### 1.1. 一些术语

这里先介绍一些关于图的术语。

+ 相邻：两个顶点通过用一条边相连，称两个顶点*相邻*，边*依附于*这两个顶点；
+ 度数：顶点的度数为依附于它的边的总数；
+ 子图：一幅图的所有边的一个子集（包括所依附的结点）组成的图；
+ 路径：由边顺序连接的一系列顶点，简单路径没有重复顶点；
+ 连通图：从任意一个顶点都存在一条路径到达另一个任意顶点；
+ 树：树是一副无环连通图，互不相连的树组成的集合称为森林；当且仅当一幅含有 V 个结点的图 G 满足下列 5 个条件之一时，它就是一棵树：
  + G 有 V-1 条边且不含有环；
  + G 有 V-1 条边且是连通的；
  + G 是连通的，但删除任意一条边都会使它不再连通；
  + G 是无环图，但添加任意一条边都会产生一条环；
  + G 中的任意一对顶点之间仅存在一条简单路径。
+ 稠密图与稀疏图：
+ 二分图：可将所有结点分为两部分，其中图的每条边所接的两个顶点术语不用的部分；

### 1.2. 无向图的表示

对于一个顶点数为 V，边数为 E 的无向图，我们可以用以下几种方式表示：

+ 邻接矩阵：使用 V 乘 V 的布尔矩阵，顶点 v 和 w 间存在连接时，则矩阵的 v 行 w 列和 w 行 v 列置为 true；
+ 边的数组：
+ 邻接表数组：使用一个以顶点为索引的列表数组，其中每个元素都是和该顶点相邻的顶点列表。

![](2020-04-10-algorithm-map/adjacency_list.png)

我们使用 *邻接表* 表示非稠密图，它将每个顶点的所有相邻顶点都保存在该顶点对应的元素所指向的一张链表中，使用这个数组可以快速访问给定顶点的邻接顶点列表。用这种表示方法，使用的空间和 V+E 成正比；添加一条边所需的时间为常数；遍历顶点 v 的所有相邻顶点所需的时间和 v 的度数成正比。

### 1.3. 深度优先搜索 DFS

我们可以通过系统地检查每一个顶点和每一条边来获取图的各种性质，在此基础上获得一些我们感兴趣的东西。在图中，很多性质是和路径相关的，我们经常需要从一个顶点移动到另一个顶点。许多图算法的抽象模型都非常简单，比如 DFS。

在讲 DFS 之前，让我们先来看看走迷宫问题，迷宫和图是非常相似的，用*通道*代替*边*，*路口*代替*顶点*，思考迷宫问题有助于我们理解 DFS。我们按照如下策略探索迷宫中的所有通道：

+ 选择一条没有标记过的通道，在你走过的路上铺一条
绳子；
+ 标记所有你第一次路过的路口和通道；
+ 当来到一个标记过的路口时（用绳子）回退到上个路口；
+ 当回退到的路口已没有可走的通道时继续回退。

绳子可以保证我们总能找到一条出路，标记保证我们不会两次经过同一个通道或路口。理解迷宫问题，对于 DFS 自然也就不在话下了，甚至描述起来更加简单：

+ 访问当前顶点，标记其标记已访问；
+ 递归地访问它所有没有被标记过的所有邻居顶点。

这就是 DFS 的全部思路了，很容易发现在递归调用中我们使用了栈这种数据结构，这对我们标记顶点而言，是 LIFO 的，这是 DFS 和 BFS 的不同之处，BFS 是 FIFO 的，我们马上会讲到 BFS。

DFS 可以有效处理许多和图有关的任务，如：

+ 连通性：给定两个顶点是否连通；
+ 单点路径：从 s 到 v 是否存在一条路径。

其实这是同一个问题，只不过路径问题需要使用额外的数组保存遍历过的路径而已，这样我们就可以从某一顶点出发构造出一棵树，树中所有结点均是该顶点可到达的。

### 1.4. 广度优先搜索 BFS

基于 DFS，我们可以确定到某一结点的是否存在路径，很自然的地我们会考虑这是不是最短路径，如果不是有没有别的办法寻找到最短路径。这正是 BFS 要解决的问题，**BFS 是很多图算法的基石，需要重点掌握**。而 DFS 无法解决这个问题，这是由它们遍历图的顺序决定的。如上面提到的，在 DFS 中，我们使用一个下压栈（递归方法体现了出来），在这种 LIFO 的规则下的探索和走迷宫探索相邻的通道非常类似。在 BFS 中，我们希望按照距离起点的距离的顺序来遍历所有的顶点，使用 FIFO 队列代替 LIFO 栈即可：
重复以下步骤直到队列为空：

+ 取队列中的下一个顶点 v 并标记它；
+ 将与 v 相邻的所有未被标记过的顶点加入队列。

同时，我们还可以使用一个数组保存遍历的路径，索引是顶点，数组的值为该顶点的已知路径上的最后一个顶点。

### 1.5. DFS 和 BFS 的总结

如同前面谈到的，DFS 和 BFS 的基本思路是一样的。在搜索中，我们先将起点存入数据结构中，然后重复以下步骤直到数据被清空：

+ 取其中的下一个顶点并标记它；
+ 将 v 的所有相邻而又未被标记的顶点加入数据结构。

两个算法的不同之处仅仅在于从数据结构中获取下一个顶点的规则不同，BFS 是最早加入的顶点，DFS 是最晚加入的顶点。这种差异得到了处理图的两种完全不同的视角，无论如何，最早我们都可以遍历所有与起点连通的顶点和边。

### 1.6. 更多问题

有了 DFS 和 BFS 两种策略，我们可以处理更多问题：

+ 连通分量；
+ 检测环；
+ 双色问题。

## 2. 有向图

**定义**：有向图是由一组*顶点*和有方向的边的组成，每条有方向的边都连接着有序的一对顶点。

![](2020-04-10-algorithm-map/directional_graph.png)

### 2.1. 有向图的表示

这里先给出有向图的一些术语。

+ 顶点的出度：该顶点指向的边的总数；
+ 顶点的入度：指向该顶点的边的总数；
+ 有向边的头：它的第一个顶点；
+ 有向边的尾：它的第二个顶点；
+ 有向路径：由一些列顶点组成，每个顶点都存在一条有向边从它指向序列中下一个顶点；
+ 有向环：一条至少含有一条边且起点和终点相同的有向路径；
+ 简单有向环：一条（除了起点和终点必须相同之外）不含有重复的顶点和边的环；
+ v 能够到达 w：v 到 w 存在有向路径（注意：这并不意味着从 w 可以达到 v）。

有向图的表示和无向图类似，我们仍然可以使用邻接表数组来表示有向图，甚至更加简单，因为边是单向的，只需保存一个相邻结点。数组索引为某个顶点，索引下的邻接表为该顶点所指向的顶点构成的链表。

### 2.2. 可达性问题

在无向图中我们处理过单点连通性问题，即判断其他顶点和给定的顶点是否连通，而在有向图中，也可以解决类似的问题，而且思路非常相似。

+ 单点可达性：给定一副有向图和起点 s，是否存在一条从 s 到达给定顶点 v 的有向图；
+ 多点可达性：给定一副图和顶点的集合，是否存在一条从集合中的任意顶点到达给定顶点 v 的路径。

解决这个问题的算法是基于 DFS 的，稍作修改即可：

```
1. 访问当前顶点，标记为已访问；
2. 递归地访问它所谓未被标记过的顶点。
```

在此基础上，稍作修改我们就可以跟进一步地求出起点 s 和 终点 v 之间的路径或最短路径，算法和无向图中的完全一样。

### 2.3. 环和有向无环图

对于有向图中环进行研究可以解决很多问题，如

+ *优先级限制下调度问题*：给定一组需要完成的任务，以及一组关于任务完成的先后次序的优先级限制。在满足限制条件的前提下应该如何安排并完成所有任务？
+ *拓扑排序*：给定一幅有向图，将所有的顶点排序，使得所有的有向边均从排在前面的元素指向排在后面的元素（或者说明无法做到这一点）。

为什么说环和这些问题是相关的呢？举个例子，考虑一个调度问题：A 必须在 B 之前完成，B 必须在 C 之前完成，C 又必须在 A 之前完成。这显然是不可能实现的，这在有向图就构成了一个环。处理这些调度问题我们必须对图中的环进行检测。

![](2020-04-10-algorithm-map/managment_and_loop.png)

有向无环图（DAG）就是一副不含有环的有向图。实现有向图中的环检测算法并不困难，我们可以基于 DFS 来解决这个问题。系统维护的递归调用栈表示的正是『当前』正在遍历的有向路径，一旦我们找到了一条有向边 v --> w 且 w 已经在栈中，就找到了一个环，如果没有，那就说明这是无环图。如果更进一步，多加一个栈，我们就可以找出构成环的顶点。

#### DAG 检测算法

```
1. 访问当前顶点，标记为已访问，标记为在当前搜索的路径的栈中
2. 对当前顶点指向的顶点
	如果未被标记，将其来源标记当前顶点，为其跳转到 1
	如果在栈中，说明图中存在环
	记录环到另一个栈中
3. 当前顶点调用完毕，标记为不在当前搜索的路径的栈中
```

可以看到这个无向图中 DFS 路径搜索算法是类似的，这再次说明了 DFS 的重要性。

#### 拓扑排序

同样的，拓扑排序也是基于 DFS 的，只需稍作修改就可以实现拓扑排序。DFS 正好只会访问每个顶点一次，如果将递归调用函数 `dfs` 的参数顶点保存在一个数据结构中，遍历这个数据结构实际上就能访问图中的所有顶点，遍历的顺序取决于这个数据结构的性质以及是在递归调用之前还是之后进行保存。我们关心下面三种顺序：

+ 前序：在递归调用之前将顶点加入队列。
+ 后序：在递归调用之后将顶点加入队列。
+ 逆后序：在递归调用之后将顶点压入栈。

可以证明，一幅有向无环图的拓扑顺序即为所有顶点的逆后续排列。

我们可以看到，拓扑排序和调度问题离不开有向环的检测，而且这两个问题可以看作是一个问题。在调度时，必须保证有向图中没有环，因此，解决任务调度类应用通常需要以下3 步：

+  指明任务和优先级条件；
+ 不断检测并去除有向图中的所有环，以确保存在可行的方案；
+ 使用拓扑排序解决调度问题。

### 2.4. 强连通性

类似无向图中的连通性，我们在有向图中定义了**强连通性**：在有向图 G 中，如果两个顶点 v 和 w 是互相可达的，则称它们是**强连通的**。联想到环的定义，我们很容易想到两个顶点是强连通的等价于它们在同一个有向环中。

有向图中的强连通性也是一种顶点之间的等价关系，满足以下性质：

+ 自反性：任意顶点 v 和自己都是强连通的。
+ 对称性：如果 v 和 w 是强连通的，那么 w 和 v 也是强连通的。
+ 传递性：如果 v 和 w 是强连通的且 w 和 x 也是强连通的，那
  么 v 和 x 也是强连通的。

强连通性将所有的顶点分为两一些等价类，每个等价类都是由相互均为强连通的顶点的最大子集组成的，我们称这些子集为**强连通分量**。对于理解有向图的结构，强连通性是一种非常重要的抽象，它突出了相互关联的几组顶点，如可以帮助决定话题分类和理解食物链中的能量流动问题。

对于强连通分量问题，我们可以使用 Kosaraju 算法来解决，本质上这个算法还是基于 DFS 的，

+ 首先对 G 进行反转，即改变所有边的指向和原来相反，得到图 H；
+ 然后对 H 进行逆后序排列；
+ 按照这个排列顺序对 G 中的顶点调用标准 DFS，每一次非标记的顶点遍历完表示做完了一个强连通分量的搜索。

![](2020-04-10-algorithm-map/kosaraju_example.png)

举个例子，如上图所示。证明如下：

![](2020-04-10-algorithm-map/kosaraju_provement.png)

## 3. 最小生成树

**加权图**是为每条边关联一个*权值*或是*成本*的图模型。这种图能够自然地表示许多应用。在一幅电路图中，边表示导线，权值则可能表示导线的长度即成本，或是信号通过这条线路所需的时间。在这些情形中，最令人感兴趣的自然是将成本最小化。我们将学习加权无向图模型并用算法回答这个问题。

**最小生成树**：给定一副加权无向图，找到它的一棵最小生成树。

在解决这个问题之前，我们需要对之前的数据结构进行一些改变。

### 3.1. Prim 算法

这是一种得到加权无向图的有效算法，基本思想如下：

+ 将一个节点加入队列，将它的所有邻边加入队列

### 3.2. Kruskal 算法



## 4. 最短路径
