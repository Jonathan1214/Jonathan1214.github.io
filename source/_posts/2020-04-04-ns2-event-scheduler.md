---
title: NS2 的介绍（三）—— 事件调度器
date: 2020-04-04 08:32:25
updated:
toc: true
categories:
  - 学习
tags:
  - 网络
  - NS2
---
在[上一篇文章](/2020/04/ns2-simple-simulation-example)中，我们从一个简单的例子出发，从零开始编写了一个 NS2 模拟用的 OTcl 脚本，我们需要在脚本中完成以下任务：

1. 创建 Simulator 对象；
2. 创建 node 对象并构建 node 间的连接 link；
3. 创建代理对象和 traffic 源对象，连接 node 和代理，连接代理和 traffic 源；
4. 创建模拟场景 scenario，即定义调度任务；
5. 开始模拟。

按照以上这些步骤编写就可完成模拟脚本编写。这篇文章中要介绍的是第 4 个步骤创建模拟场景的详细信息，我们将讨论 NS2 中的离散事件调度器。
<!-- more -->
如[第一篇文章](/2020/04/02/ns2-simulation-overview)中谈到的，在 NS2 中，事件调度器主要是由一些网络组件来使用，组件们模拟 packet 的处理时需要调度程序作为延时器或计时器。如下图展示，每一个网络对象使用一个时间调度器，图中需要注意：
（1）网络对象发出一个事件那么它就要在预定的时间点上处理这个事件；
（2）网络对象间的数据路径和事件路径不相同；
若深入到代码层面，包在网络对象中传递时，发送方使用 `send(Packet* p){target_->recv(p);` 语句发送，接收方使用 `recv(Packet*, Handler* h = 0)` 方法接收。
<div align="center" class="img">
    <img src="/assets/img/2020/discrete_event_scheduler.png" alt="discrete_event_scheduler" width="750">
    <span align="center" style="color:#999">离散事件调度器</span>
</div>
NS2 实现了两种事件调度器，实时调度器和非实时调度器。非实时调度器有三种实现，分别为 List、Heap 和 Calendar，它们逻辑上是一样的，之所以有这么多实现，是由于向下兼容的原因。默认的非实时调度器是 Calender 方式实现的。实时调度器是为仿真 emulation 使用的，允许仿真器 simulator 和真实的网络交互。下面这个就是一个指定事件调度器的例子。

    set ns [new Simulator]
    $ns use-scheduler Heap

事件调度器还可以调度模拟事件，比如启动一个 FTP 应用或者结束模拟。事件调度器对象本身有一些模拟调度成员函数，比如 `at <time> "<string>"`，它就可以在发起一个在特定的模拟时间 <time\> 发生的叫做 `AtEvent` 的事件。`AtEvent` 其实是 `Event` 类的子类，它扩展了额外的变量保存 `at <time> "<string>"` 中的 `string`，尽管有扩展，它在事件调度器中和一般的事件还是被相同对待的。模拟开始后，当模拟时间到达事件队列中的 AtEvent 应该被调度的时间时，该 `AtEvent` 就会被传递给一个 `AtEvent Handler`，`AtEvent Handler` 只被创建一次并处理所有的的 `AtEvent`，`AtEvent` 的 <string\> 确定的 OTcl 命令也会被执行。下面是一个模拟事件调度示例：

    set ns [new Simulator]
    $ns use-scheduler Heap
    $ns at 300.5 "complete_sim"

    proc complete_sim {} {...}

注意到在上面的例子中，`at <time> "<string>"` 是 Simulator 对象 ns 的成员函数，但是我们要记住，Simulator 对象仅仅只是起到一个用户接口的作用，事实上它会去调用网络对象或者调度器对象的成员函数，由它们真正地完成工作。下面是一个函数列表和简单说明，这些函数就是 Simulator 对象用来接口调度器成员函数的成员函数。

| 成员函数 | 说明 |
| :---- | :---- |
| Simulator instproc now | 返回调度器对现在时间的 notion |
| Simulator isntproc at args | 在特定的时间调度执行代码|
| Simulator instproc at-now args | 立即调度执行代码 |
| Simulator instproc after n args | n 秒后调度执行代码 |
| Simulator instproc run args | 启动调度器 |
| Simulator instproc halt | 停止或赞同调度器 |

---
参考：[WPI](http://nile.wpi.edu.cn/NS/)
