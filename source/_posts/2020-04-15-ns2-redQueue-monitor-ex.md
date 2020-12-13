---
title: NS2 的介绍（七）—— RED 队列监视示例
date: 2020-04-15 14:15:03
updated:
categories:
  - 学习
tags:
  - 网络
  - NS2
---

本文将展示一个 RED 队列监视示例。下面这段 OTcl 脚本建立了如图所示网络拓扑然后运行模拟场景，可以看到，在 r1 和 r2 间的 link 使用的 RED 队列可以保存至多 25 个 packet，我们通过测量当前队列和平均队列大小的动态变化，以观察 RED 队列是如何工作的。点击下载代码<a href="/downloads/code/red.tcl"> red.tcl </a>。<!-- more -->

{% asset_img red_queue_monitor_setup.png '网络设置' %}

{% include_code lang:tcl red.tcl %}

有几件事需要注意。首先，更高级的 Simulator 对象成员函数 `create-connection` 被用于创建 TCP 连接。其次，仔细观察代码中的队列跟踪部分，可以发现我们创建了一个指向 RED 队列对象的变量，调用它的成员函数 `trace` 监视当前队列大小（cur_q）和平均队列大小（avg_），然后把结果写入文件 `all.q` 中。

运行结果：
{% asset_img result.png '运行结果' %}

---
参考：[WPI](http://nile.wpi.edu.cn/NS/)