---
title: NS2 的介绍（二）—— 模拟示例
date: 2020-04-03 10:25:25
updated:
toc: true
categories:
  - 学习
tags:
  - 网络
  - NS2
---
我们在前[一篇文章](/2020/04/ns2-simulation-overview)中简单介绍了 NS2，它是一个离散事件驱动的网络模拟器，从具体实现来看，它就是一个 OTcl 脚本解释器，由模拟事件调度程序、网络组件对象库和网络启动(plumbing)模块库组成。文中还介绍了这些部分是如何一起协同实现网络模拟的。有了关于 NS2 的基本概念，下面就来看一个具体的模拟示例，看看 OTcl 脚本如何编写，如何进行一个网络模拟吧。
<!-- more -->
## OTcl 脚本编写

前面提到，NS2 是一个 OTcl 解释器，在它上面进行模拟就需要编写 OTcl 脚本。在介绍 OTcl 编写之前，我们需要知道 Tcl 和 OTcl 的关系就像 C 和 C++ 的关系一样，在前者的基础上，后者增加了面向对象特性，下面就来看看 Tcl 和 OTcl 脚本如何编写吧。

### Tcl 脚本

一份 Tcl 脚本如下所示，需要关注的点如表所示，详细可以参考[易百教程](https://yiibai.com/tcl)，对于基本的 NS2 脚本编写，了解这些就够了。

| 操作 | 关键字 | 格式 | 示例 |
| :---- | :---- | :---- | :---- |
| 定义 procedure | `proc` | `proc <procname> {<argumentlist>} {<contents>}` | 第 2 行 |
| 定义变量 | `set` | `set <variablename> <variablevalue>` | 第 3 行 |
| 表达式值替换 | `expr` | `[expr <expression>]` | 第 5 行 |
| 变量值替换 | `$` | `$<variablename>` | 第 5 行 |
| 输出 | `puts` | `puts "<contents>"` | 第 9 行 |
| for 循环 | `for` | `for {<initial>} {<condition>} {actioneveryloop} {<mainLoopExpression>}`| 第 7 行 |
| if 条件选择语句 | `if` | `if {<condition>} {<expression>}` | 第 8 行 |

{% include_code ex-tcl.tcl lang:tcl %}

将文件保存为 `ex-tcl.tcl`，然后在Shell中执行 `ns ex-tcl.tcl`，得到的的输出如下：

```
k < 5, pow = 1.0
k < 5, pow = 1120.0
k < 5, pow = 1254400.0
k < 5, pow = 1404928000.0
k < 5, pow = 1573519360000.0
k >= 5, mod = 0
k >= 5, mod = 4
k >= 5, mod = 0
k >= 5, mod = 0
k >= 5, mod = 4
```

### OTcl 脚本

相比于 Tcl，OTcl 增加了面向对象功能，下面这个例子展示了 OTcl 中对象是如何被创建和使用的。作为一个 NS2 的使用者，我们可能不会需要编写自己的 OTcl 对象，但是了解它们还是很有帮助的，因为我们在 NS2 模拟中使用的所有的对象，无论它们是 C++ 编写后连接到 OTcl 还是是直接使用OTcl 编写的，它们本质上都是 OTcl 对象。

下面这个例子中创建了两个类 `mom` 和 `kid`，它们都有成员函数 `greet`，声明类之后，在第 17~19 行我们对类进行了实例化，并定义了实例的成员变量的值，然后在 23、24 行调用了两个实例的成员函数。从代码从我们很容易可以看出：

+ 如何对类进行实例化？
+ 如何改变类实例的成员变量的值？
+ 如何调用类实例的成员函数？

那么如何定义一个类和子类呢？定义一个类需要使用关键字 `Class` 创建一个类，使用关键字 `instproc` 定义类的成员函数。类的继承使用关键字 `-superclass`，在成员函数中，`$self` 的作用就好像 C++ 中的 `this` 指针一样，关键字 `instvar` 检查后面紧跟的变量名是否已在类或父类中被声明，如果已经被声明，那这个变量就是已声明变量的引用，反之，这就是一个新的变量声明。最后，创建一个类实例，需要使用关键字 `new`。

{% include_code ex-otcl.tcl lang:tcl %}

文件保存为 `ex-otcl.tcl`，在 Bash 中执行 `ns ex-otcl.tcl`，得到如下的输出：

```
45 year old mom say:
        How are you doing
15 year old kid say:
        What's up, dude?'
```

## 简单的 NS2 模拟示例

现在我们已经知道了基本的 OTcl 脚本是如何编写的了，现在来看看如何编写一个执行 NS2 模拟的 OTcl 脚本吧。
下面的 `ns-simple.tcl` OTcl 脚本中进行了简单的网络配置，执行如图所示的模拟方案。下载代码后，在 Bash 中执行 `ns ns-simple.tcl` 即可。
<div align="center" class="img">
    <img src="/assets/img/2020/simple_simulation_scenario.png" alt="structure_of_ns2" width="750">
    <span align="center" style="color:#999">一个简单的网络拓扑和模拟方案示意图</span>
</div>
从图中可以看到，这个网络包括四个节点：n0，n1，n2和n3。n0 和 n2 间是双向连接，n1 和 n2 间的连接有 2Mpbs 的带宽，传输时延为 10ms。n2 和 n3 之间为双向连接，传输带宽为 1.7Mbps，传输时延为 20ms。每个节点都使用一个 DropTail 队列，队列最大长度为 10。
n0 节点上绑定了一个 tcp 代理，该代理和绑定在 n3 上的『sink』代理间构建了一条连接 (connection)。默认情况下，tcp 代理可以生成的最大 packet 为 1KByte。tcp『sink』代理生成确认接受分组 P 的 ACK 并将 ACk 发送给分组的发送者（即发送分组 P 的 tcp 代理），然后释放接收到的分组 P。
n1 节点上绑定了一个 udp 代理，该代理和绑定在 n3 上的『null』代理间建立了一条连接。『null』代理字释放接收到的 packet，不会向 packet 的发送方发送 ACK。
ftp 和 cbr 是 traffic 生成器，分别绑定到 tcp 和 udp 代理上。cbr 被设定为可以生成以 1Mbps 的速率生成 1KByte 大小的 packet，它在 0.1s 时开始工作到 4.5s 时停止，而 ftp 在 1.0s 时开始工作到 4.0s 停止。

{% include_code ns-simple.tcl lang:tcl %}

### 从 Simulator 对象开始网络的基本设置

下面是对上述脚本的解释，总体上来看，NS 脚本从创建一个 Simulator 对象实例开始。
**注意**：代码中，`<>` 包围的内容在使用时要按照实际情况替代成正确的内容。

+ `set ns [new Simulator]`：生成一个 NS2 simulator 对象实例为 ns。这一行代码完成了一些工作：
    + 初始化 packet 格式
    + 创建一个调度器（默认为 calendar 调度器）
    + 选择默认的地址格式

Simulator 的成员函数可以完成如下工作：

+ 创建一些复合对象，如节点 node 和 连接 link
+ 连接网络组件对象
+ 设置网络组件对象的参数
+ 创建代理间的连接，如 tcp 和 sink 间的连接
+ 明确 NAM 展示的选项等等

大多数成员函数用于模拟设置（如 plumbing 函数）和调度，也有一些用于 NAM 展示的设置。Simulator 对象成员函数在文件 `ns-2.35/tcl/lib/ns-lib.tcl` 中实现。

+ `$ns color <fid> <color>`：为流 id 即 fid 确定的流中 packet 设置颜色。该 Simulator 对象的成员函数为 NAM 展示服务，对实际的模拟有影响。
+ `$ns namtrace-all <file-descrption>`：这个成员函数告诉模拟器（simulator）按照 NAM 的输入的格式记录模拟痕迹（trace）到文件中，同时也给出了 `$ns flush-trace` 命令要写入的文件。类似的，函数 `trace-all` 用来记录模拟痕迹（trace），但是是基本的格式。
+ `proc finish {}`：一个模拟结束够调用的函数，通过 `$ns at 5.0 "finish"` 调用。在函数中，定义了模拟后的后续操作，如保存文件。
+ `set n0 [$ns node]`：成员函数 `node` 创建一个节点 node0。NS2 中的节点是一个复合类，由地址和端口分类器组成。用户创建节点时，也可以分别创建一个地址和端口分类器对象，然后再把它们连接起来，但是这个 Simulator 成员函数让节点创建变得简单。文件 `ns-2.35/tcl/lib/ns-lib.tcl` 和 `ns-2.35/tcl/lib/ns-node.tcl` 中有关于创建节点的详细信息。
+ `$ns duplex-link <node1> <node2> <bandwidth> <delay> <queue-type>`：创建两条单向连接，指定带宽和时延，然后连接声明的两个节点。在 NS2 中，节点的输出队列实现为一个连接的一部分，因此用户在创建连接时要指明队列类型 queue-type。上面的代码中使用的 DropTail 队列，如果想使用其他队列，修改队列类型即可。连接的实现在下一篇文章会提到，类似节点，连接也是一个复合类型，用户可以创建出它的子对象然后把他们和节点连接起来。有关连接的源代码在文件 `ns-2.35/tcl/lib/ns-lib.tcl` 和 `ns-2.35/tcl/lib/ns-link.tcl` 中。在连接模块中，我们可以进行很多个性化的操作，详请参考 NS2 文档。
+ `$ns queue-limit <node1> <node2> <number>`：设置两条连接 node1 和 node2 单向连接的队列大小。
+ `$ns duplex-link-op <node1> <node2> ...`：NAM 展示的设置，即设置节点的位置。

### 设置代理和 traffic 源

现在，基本的网络设置以及完成了，下一就是启动 traffic 代理，如 TCP 和 UDP，这两个代理的 traffic 源分别为 FTP 和 CBR，然后把代理绑定到对应的节点上，把 traffic 绑定到对应的代理上。

+ `set <tcpname> [new Agent/TCP]`：创建一个名为 tcpname 的代理。总的来说，用户都是以这种方式创建任何代理或 traffic 源。代理和 traffic 源其实是基本对象（非复合对象），它们是基于 C++ 实现的，然后连接到 OTcl 上，因此没有特殊的 Simulator 对象的成员函数来创建这些对象实例。用户应该知晓这些代理和 traffic 源对象的类名，如 Agent/TCP，Agent/TCPSink，Application/FTP 等等，详细可参看 NS2 的文档，在文件 `ns-2.35/tcl/lib/ns-default.tcl` 也可以找到相关信息，文件中包含了可使用的网络对象的默认参数值设置，因此，它可以很好的告诉我们哪种网络对象在 NS2 中可以使用，可设置的参数有哪些。
+ `$ns attach-agent <node> <agent>`：为节点绑定代理。事实上，这个`attach-agent`函数调用节点的成员函数`attach`来完成绑定工作，因此也可以使用如 `$n0 attach $tcp0` 将 节点 代理 tcp0 绑定到节点 n0 上。
+ `$ns connect <agent1> <agent2>`：创建了两个代理之后，下一步就是建立逻辑网络连接，通过这一行语句，代理间将对方的网络和端口地址设置为目的地址，从而建立网络连接。

### 编写模拟场景

假设所有的网络设置已经完成了，接下来就该编写模拟场景 scenario。Simulator 对象有许多调度成员函数，下面这个是最经常被使用的：

+ `$ns at <time> "<string>"`：让调度器在指定的 time 时执行 string 中的命令。如 `$ns at 0.1 "$cbr start"`，让调度器调用 CBR traffic 源对象的一个名为 start 的成员函数，start 会开始启动 CBR 发送数据。在 NS2 中，一个 traffic 源通常不会发生真实的数据，它会通知下层的代理『有一些数据要发生』，代理就会知道有多少数据要发生，然后由代理创建 packet 并发送出去。

### 开始模拟

配置好网络，写好调度程序和指定模拟后的数据保存操作之后，最后开始模拟即可，脚本中的最后一句：`$ns run` 声明开始模拟。

---
参考：[WPI](http://nile.wpi.edu.cn/NS/)
