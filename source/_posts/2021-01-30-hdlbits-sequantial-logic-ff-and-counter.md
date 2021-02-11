---
title: 『HDLbits』时序逻辑之 FF 和 Counter
copyright: true
categories:
  - 学习
tags:
  - verilog
  - FPGA
date: 2021-01-30 14:06:01
updated:
---


刷了一天 hdlbits 了，放几道时序逻辑电路设计的题上来，对于现在的我来说，这些问题都算不得难了，因为电路都很简单，只是要用 Verilog 实现，但真正要设计电路的问题对我而言就相对困难了，比如文中的 [Dualedge](#Dualedge)，难在电路设计，而不是 Verilog 实现，后者纯粹是个体力活，比如 [Count clock](#Count-clock)，需要加油啊。

<!--more-->

## Edgecapture

原文链接：[Edgecapture](https://hdlbits.01xz.net/wiki/Edgecapture)。

For each bit in a 32-bit vector, capture when the input signal changes from 1 in one clock cycle to 0 the next. "Capture" means that the output will remain 1 until the register is reset (synchronous reset).

Each output bit behaves like a SR flip-flop: The output bit should be set (to 1) the cycle after a 1 to 0 transition occurs. The output bit should be reset (to 0) at the positive clock edge when reset is high. If both of the above events occur at the same time, reset has precedence. In the last 4 cycles of the example waveform below, the 'reset' event occurs one cycle earlier than the 'set' event, so there is no conflict here.

In the example waveform below, reset, in[1] and out[1] are shown again separately for clarity.

保持先前为 1 的状态，最好的办法莫过于使用`与AND`了，如 `out <= out | (reg_in & (~in))` 简单一句就完成抓取下降沿的任务，同理易知抓取上升沿即 `out <= out | ((~reg_in) & in)`。

 {% asset_img image-20210130143822445.png %}

```verilog
module top_module (
    input clk,
    input reset,
    input [31:0] in,
    output reg [31:0] out
);
    reg [31:0] reg_in;
    always @(posedge clk) begin
        reg_in <= in;
    end
    
    always @(posedge clk) begin
        if ( reset )
            out <= 32'd0;
        else
            out <= out | (reg_in & (~in));
    end

endmodule
```

## Dualedge

原文链接：[Dualedge](https://hdlbits.01xz.net/wiki/Dualedge)。

果然，碰到真正的时序电路设计问题我就直接懵了。下面的答案是在网上抄的，实在是惭愧。

You're familiar with flip-flops that are triggered on the positive edge of the clock, or negative edge of the clock. A dual-edge triggered flip-flop is triggered on both edges of the clock. However, FPGAs don't have dual-edge triggered flip-flops, and `always @(posedge clk or negedge clk)` is not accepted as a legal sensitivity list.

Build a circuit that functionally behaves like a dual-edge triggered flip-flop:

 {% asset_img image-20210130150619632.png %}

```verilog
module top_module (
    input clk,
    input d,
    output q
);
    reg q_d1;
    reg q_d2;
    always@(posedge clk)begin
        q_d1 <= d ^ q_d2;
    end
    always@(negedge clk)begin
        q_d2 <= d ^ q_d1;
    end
    assign q = q_d1 ^ q_d2;
endmodule
```

## Exams/ece241 2014 q7a

原文链接：[Exams/ece241 2014 q7a](https://hdlbits.01xz.net/wiki/Exams/ece241_2014_q7a)。

正确理解全部的需求，否则会有意想不到的BUG。

Design a 1-12 counter with the following inputs and outputs:

- **Reset** Synchronous active-high reset that forces the counter to 1
- **Enable** Set high for the counter to run
- **Clk** Positive edge-triggered clock input
- **Q[3:0]** The output of the counter
- **c_enable, c_load, c_d[3:0]** Control signals going to the provided 4-bit counter, so correct operation can be verified.

You have the following components available:

- the 4-bit binary counter (**count4**) below, which has Enable and synchronous parallel-load inputs (load has higher priority than enable). The **count4** module is provided to you. Instantiate it in your circuit.
- logic gates

```
module count4(
	input clk,
	input enable,
	input load,
	input [3:0] d,
	output reg [3:0] Q
);
```

The **c_enable**, **c_load**, and **c_d** outputs are the signals that go to the internal counter's **enable**, **load**, and **d** inputs, respectively. Their purpose is to allow these signals to be checked for correctness.

```verilog
module top_module (
    input clk,
    input reset,
    input enable,
    output [3:0] Q,
    output c_enable,
    output c_load,
    output [3:0] c_d
); //
    
    count4 the_counter (clk, c_enable, c_load, c_d, Q );
    
    assign c_d = 4'd1;
    assign c_enable = enable;
    assign c_load = reset | (Q == 4'd12 && enable);

endmodule
```

注意最后一条 assign 语句，`Q == 4'd12 && enable`，如果不测试，很容易忘记加 `enable` 条件，产生意想不到的 错误，我自己在测试的时候怎么才能发现这样的问题呢？hdlbits 上的 checker 是怎么做的，我很想知道。

## Count clock

原文地址：[Count clock](https://hdlbits.01xz.net/wiki/Count_clock)

Create a set of counters suitable for use as a 12-hour clock (with am/pm indicator). Your counters are clocked by a fast-running `clk`, with a pulse on `ena` whenever your clock should increment (i.e., once per second).

`reset` resets the clock to 12:00 AM. `pm` is 0 for AM and 1 for PM. `hh`, `mm`, and `ss` are two **BCD** (Binary-Coded Decimal) digits each for hours (01-12), minutes (00-59), and seconds (00-59). Reset has higher priority than enable, and can occur even when not enabled.

The following timing diagram shows the rollover behaviour from `11:59:59 AM` to `12:00:00 PM` and the synchronous reset and enable behaviour.

 {% asset_img image-20210130204152683.png %}

```verilog
module top_module(
    input clk,
    input reset,
    input ena,
    output reg pm,
    output reg [7:0] hh,
    output reg [7:0] mm,
    output reg [7:0] ss); 
    
    wire ena_mm = (ss == 8'h59) & ena;
    wire ena_hh = ena & (ss == 8'h59) & (mm == 8'h59);
    
    // ss
    always @(posedge clk) begin
        if ( reset )
            ss <= 0;
        else if ( ena ) begin
            if ( ss == 8'h59 )
            	ss <= 0;
            else if ( ss[3:0] == 4'd9 && ss[7:4] != 4'd5 )
                ss <= {ss[7:4]+1'b1, 4'd0};
            else
                ss[3:0] <= ss[3:0] + 1'b1;
        end
    end
        
    // mm
    always @(posedge clk) begin
        if ( reset )
            mm <= 0;
        else if ( ena_mm ) begin
            if ( mm == 8'h59 )
                mm <= 0;
            else if ( mm[3:0] == 4'd9 && mm[7:4] != 4'd5 )
                mm <= {mm[7:4] + 1'b1, 4'd0};
            else
                mm[3:0] <= mm[3:0] + 1'b1;
        end
    end
    
    // hh
    always @(posedge clk) begin
        if ( reset )
            hh <= 8'h12;
        else if ( ena_hh ) begin
            if ( hh == 8'h12 )
                hh <= 8'h01;
            else if ( hh[3:0] == 4'd9 )
                hh <= {hh[7:4]+1'b1, 4'd0};
            else
                hh[3:0] <= hh[3:0] + 1'b1;  
        end
            
    end
    
    always @(posedge clk) begin
        if ( reset )
            pm <= 0;
        else if ( ena_hh && hh == 8'h11 )
            pm <= ~pm;
        else
            pm <= pm;
    end
endmodule
```

