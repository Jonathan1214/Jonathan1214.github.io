---
title: 一点数字电路设计的感悟
date: 2020-12-01 10:41:12
updated:
categories:
  - 生活
tags:
  - sr-log
  - 记录
---

惊呼：已经12月了！

现在每日牵挂的无非是课设二字，近日还算专心钻研数字电路设计，也算是知道了一点东西，有一点感悟，不妨写下来，让这种感觉更加准确。
<!--more-->
数字电路设计，无非是时序逻辑电路和组合逻辑电路，在 FPGA 设计中，就是带触发器的同步电路设计和纯组合电路设计，浅显的理解可以认为是阻塞赋值和非阻塞赋值的区别。话虽说得简单，但是实际做起来倒真的不容易，就比如我几天前写的那个串口接收和发送的代码，时序总是不对，后面多看了看别人的设计，才发现自己真是太嫩了，这种设计自然是有比较特定的规律。

## 边沿检测

边沿检测可算是最最经典的电路设计了，实际当中却是处处会用到。一个典型的检测电路如下：

```verilog
module Edge_detect(
	input clk,		// 时钟
	input rst_n,	// 复位信号
	input SigIn,	// 输入信号 
	output SigOut,  // 同步之后的输出信号
	output down,    // 检测到下降沿产生一个脉冲
	output up	    // 检测上升沿产生一个脉冲
);
	
	reg [2:0] ToggleSigIn;	// 三级寄存器，前两级用于同步信号
	always @(posedge clk or negedge rst_n) begin
		if (~rst_n) begin
			ToggleSigIn <= 0;
		end
		else begin
			// 移位寄存
			ToggleSigIn <= {ToggleSigIn[1:0], SigIn};
		end
	end
	
	// 同步后的信号直接作为输出
	assign SigOut = ToggleSigIn[2];	
	// 前一时刻为低电平 后一时刻为高电平 下降沿出现
	assign down   = (~ToggleSigIn[2] & ToggleSigIn[1]);
	// 前一时刻为高电平 后一时刻为低电平 下降沿出现
	assign up     = (ToggleSigIn[2] & ~ToggleSigIn[1]);
endmodule
```

看起来非常简单，但在实际使用中却是必不可少又十分有效的，譬如在串口接收中就需要简单信号线上下降沿的产生，以检测信号到来，当然，检测之前，做一次数据同步是必不可少的。