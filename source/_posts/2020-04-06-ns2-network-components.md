---
title: NS2 的介绍（四）—— 网络组件
categories:
  - 学习
tags:
  - 网络
  - NS2
date: 2020-04-06 09:30:03
updated:
---

我们在[前文](/2020/04/ns2-event-scheduler)讨论 NS2 中一个非常重要的组成——事件调度器，这篇文章将讨论 NS2 另一个关键的组成——网络组件，主要是复合网络组件。
<!-- more -->
下图展示了 NS2 中部分 OTcl 类的部分体系结构，有助于我们理解基本的网络组件（network component），在[这个链接](http://www.sop.inria.fr/rodeo/personnel/Antonie.Clerget/ns)中可以找到 NS2 类的完整的体系结构。
<p align="center" class="img">
    <img src="/assets/img/2020/partial_class_hierarchy.png" alt="partial_class_hierarchy" width="500">
    <span align="center" style="color:#999">类的部分体系结构</span>
</p>
层级的根是 TclObject 类，它是所有 OTcl 库对象的父类，如 scheduler（调度器），network component（网络组件），（timer）计时器和其他，包括 NAM 相关的类。NsObject 类是 OTclObject 的直接子类，同时也是所有基本 network component（网络组件）对象的父类，这些 network component 构成复合网络对象如 node （节点）和 link （连接），用来处理 packet。基于可能的输出 data path （数据路径）的数量，基本 network component （网络组件）进一步分为两类，Connector（连接器）和 Classifier（分类器），只有一个输出 data path（数据路径）的网络对象归到 Connector（连接器）下，而有多条输出 data path（数据路径）的归到 Classifier （分类器）下。

## 节点和路由选择

node（节点）是一个由节点入口对象和分类器构成的复合对象，如下图所示，NS2 中有两种 node （节点），unicast（单播）节点和 multicast （多播）节点。单播节点中有两个分类器，一个是负责单播路由选择的地址分类器，另一个是端口分类器。类似地，多播节点也有两个分类器，一个分类器负责区分多播 packet 和单播 packet，另一个多播分类器负责多播路由选择。
<p align="center" class="img">
    <img src="/assets/img/2020/node.png" alt="node" width="600">
    <span align="center" style="color:#999">节点</span>
</p>
在 NS2 中，默认节点设置为单播，如要使用多播节点，需要在 OTcl 脚本中显式声明，创建 scheduler（调度器）对象后立即声明，而后所有的节点都会被创建为多播节点。确定节点类型后，使用者还需要手动选择一个路由选择协议，不可使用默认协议。

+ unicast：
  + `$ns rtproto <type>`
  + `<type>`：Static，Session，DV，cost，multi-path
+ multicast：
  + `$ns multicast` 放在 `set $ns [new Scheduler]` 后
  + `$ns mrtproto <type>`
  + `<type>`：CtrMCast，DM，ST，BST

关于路由选择的更多信息，可以参考 [NS2 手册](http://www.isi.edu/nsnam/ns/ns-documentation.html)。

## 连接

link（连接）是 NS2 中另一个主要的复合对象，当使用者使用 Simulator 对象的 `duplex-link` 成员函数，就可以创建一个双向连接，该连接包括两条单向连接，分别连接的双方，如下图所示。

另一个要注意到是，节点的输出队列其实被实现为 simplex （单向）连接的一部分。从队列中 dequeue （出队）的 packet被传递给模拟连接延时的 Delay（延时）对象，而从队列中 drop （抛弃）的 packet 的被传递给一个 Null 代理然后被释放。最后，TTL 对象为每一个接受到的 packet 计算（time to live parameter）生命参数的时间，并更新 packet 的 TTL 字段。
<div align="center" class="img">
    <img src="/assets/img/2020/link.png" alt="link" width="400">
    <span align="center" style="color:#999">连接</span>
</div>

### 追踪

在 NS2 中，网络活动在单向连接中被记录，如果 simulator （模拟器）被指引去追踪网络活动（使用 `$ns trace-all <file>` 或 `$ns namtrace-all <file>`），那么 link （连接）在创建后，会有如下图所示的 trace（追踪）对象插入其中。使用者也可以在给定的源节点和目的节点间自定义一个 type 类型的 trace 对象，使用 `creat-trace {type <file> <src> <dst>}` 命令即可。

当插入到 link 中的 trace 对象（如 EnqT，DeqT 和 RecvT）受到一个 packet 时，它会向特定的 trace 文件中写入信息，且不需要消耗模拟时间，然后把该 packet 传递给下一个网络对象。trace 的格式讲在后面讨论。
<div align="center" class="img">
    <img src="/assets/img/2020/link_with_trace.png" alt="link_with_trace" width="750">
    <span align="center" style="color:#999">插入了 trace 对象的连接</span>
</div>

### 队列监视器

本质上，tracing （追踪）对象被设计成可以记录 packet 的到达所在位置的时间。尽管使用者可以从 trace 中获得足够多的信息，如果他们对特定输出队列中发生的事的细节感兴趣，他们可以通过一些设置来获取这些信息。比如，如果使用者对 RED 队列的行为感兴趣，想计算平均队列大小的 dynamics 和某一特定 RED 队列的实时队列大小，或者其他有关监视队列的需求，队列监视器就可以有所帮助。队列监视行为使用队列监视器对象和 snoop 队列对象实现，如下图所示。

当一个 packet 到达时，snoop 队列对象通知 queue monitor（队列监视器）该事件，由队列监视器监视队列。后续会给出一个 RED 队列监视的例子，详细情况可以参考那个例子。现在只需要注意到，snoop 队列对象除了图中所示的用法，它还可以与 tracing （追踪）对象并行使用。
<div align="center" class="img">
    <img src="/assets/img/2020/link_with_snoop_queue.png" alt="link_with_snoop_queue" width="750">
    <span align="center" style="color:#999">插入了 trace 对象的连接</span>
</div>

## 一个 packet 流动的例子

到现在为止，我们分析了两个最重要的网络组件——节点和连接。下图展示了一个模拟网络建立和 packet 流动的内部情况。
网络由两个节点 n0 和 n1 组成，网络地址分别 0 和 1。绑定在 n0 上的一个 TCP 代理使用端口 0 与 绑定在 n1 上的使用端口 0 的 TCP sink 对象通信。最后，一个 FTP 应用绑定到 TCP 代理上，请求发送一些数据。
注意，下图没有显示出 FTP 在 TCP 上的具体行为，仅仅展示仿真网络和 packet 流动的详细内部情况。

<div align="center" class="img">
    <img src="/assets/img/2020/packet_flow.png" alt="packet_flow" width="750">
    <span align="center" style="color:#999">插入了 trace 对象的连接</span>
</div>

---
参考：[WPI](http://nile.wpi.edu.cn/NS/)
