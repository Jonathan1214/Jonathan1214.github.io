---
title: NS2 的介绍（六）—— trace 分析示例
date: 2020-04-08 12:41:36
updated:
toc: true
categories:
 - 学习
tags:
 - 网络
 - NS2
---
本文将展示一个 trace 分析示例，从中可以知道如何从 NS2 中生成 trace，如何解释 trace，如何从 trace 中得到有用的信息。在 {% post_link ns2-simple-simulation-example '模拟示例' %} 给出的代码 {% asset_link ns-simple.tcl %} 中的第 15、16 行，我们打开了一个 trace 文件，在 finish 步骤中，我们向 trace 文件中写入了 trace 信息。<!-- more -->

{% codeblock lang:tcl %}
#...
#open trace file
set f [open out.tr w]
$ns trace-all $f
#...
{% endcodeblock %}

执行代码{% asset_link ns-simple.tcl %}会生成一个 NAM trace 文件，该文件作为 NAM 的输入，同时还会生成一个名为 out.tr 的文件，该文件用于我们的模拟分析。下图展示了 trace 的格式和来自 out.tr 的 trace 数据示例。

{% asset_img trace_format_example.png 'trace 文件格式与示例' %}
每一个 trace 行依次为以下部分：

+ 事件描述符：+，-，d，r
+ 事件发生的模拟时间，单位：秒
+ 发起事件的节点
+ 接受的节点
+ packet 类型
+ packet 大小，单位 Byte
+ 分隔符：------
+ flow id：使用者在 OTcl 脚本中定义的 flow id。在模拟中用不到，可用于后续分析
+ 源地址
+ 目的地址
+ 网络层协议下 packet 序列号：UDP 协议不需要使用序列号号但也会携带，便于分析
+ packet id：每一个 packet 编号唯一

拿到模拟数据后，我们要做的就是筛选出需要的信息，并把它们转换成更容易理解的形式然后分析。下面是一简单的数据转换示例，对上面得到的 out.tr 文件，在终端中执行 `cat out.tr | grep " 2 3 cbr " | grep ^r | awk 'BEGIN {oldtime=0;oldpacket=0;} {dif=$12-oldpacket;if(dif==0) dif=1; if(dif>0) {printf("%d\t%f\n",$12,($2-oldtime)/dif); oldtime=$2;oldpacket=$12}}' > jitter.txt`，即可在目录下得到一个输出文件 jitter.txt。该命令从 trace 中提取节点 3 从 2 中接收 packet 的事件，并计算接收当前 packet 距离接收上一个 packet 的 packet 时延（接收时间差/packetID差）。使用 gnuplot 可以画出如下图像，X 轴为 packet 序列号，Y 轴为模拟时间（单位：秒）。

这个例子中，仿真后的分析在 shell 终端中进行，但是这些处理也可以在输入的 OTcl 脚本中进行，我们将在下一节讨论。

---
参考：[WPI](http://nile.wpi.edu.cn/NS/)
