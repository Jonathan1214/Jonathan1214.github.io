---
title: 『NC』verilog 序列检测
copyright: true
notshow: false
date: 2022-08-01 10:27:53
updated:
categories:
  - verilog
  - cheatsheet
tags:
  - verilog
  - nowcoder
---

牛客上 Verilog 练习题的答案合集。我对这些题目的评价是比较坑，练习的快感不如 HDLbits，而且测试非常不专业，但还是值得一做的。

[verilog题目集](https://www.nowcoder.com/exam/oj?page=1&tab=Verilog%E7%AF%87&topicId=302)

+ VL25 输入序列连续的序列检测
+ VL26 含无关项的序列检测
+ VL27 不重叠序列检测
+ VL28 输入序列不连续的序列检测

<!-- more -->

## VL25 输入序列连续的序列检测

状态机法：

```verilog
`timescale 1ns/1ns
module sequence_detect(
    input clk,
    input rst_n,
    input a,
    output reg match
    );

    parameter idle = 0, s0 = 1, s1 = 2, s2 = 3;
    parameter s3 = 4, s4 = 5, s5 = 6, s6 = 7, s7 = 8;
    reg [3:0] state;
    reg [3:0] nstate;

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0)
            state <= idle;
        else
            state <= nstate;
    end

    always @(*) begin
        nstate = idle;
        case (state)
            idle: nstate = a ? idle : s0;
            s0 : nstate = a == 1'b1 ? s1 : s0;
            s1 : nstate = a == 1'b1 ? s2 : s0;
            s2 : nstate = a == 1'b1 ? s3 : s0;
            s3 : nstate = a == 1'b0 ? s4 : idle;
            s4 : nstate = a == 1'b0 ? s5 : s1;
            s5 : nstate = a == 1'b0 ? s6 : s1;
            s6 : nstate = a == 1'b1 ? s7 : s0;
            s7 : nstate = a == 1'b1 ? s2 : s0;
            default : nstate = idle;
        endcase
    end

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0)
            match <= 1'b0;
        else if (state == s7)
            match <= 1'b1;
        else
            match <= 1'b0;
    end

endmodule
```

移位寄存器法：

## VL26 含无关项的序列检测

状态机法：

```verilog
`timescale 1ns/1ns
module sequence_detect(
    input clk,
    input rst_n,
    input a,
    output reg match
    );

    reg [3:0] state, nstate;
    parameter Idle = 0, s1 = 1, s2 = 2, s3 = 3, s4 = 4, s5 = 5; 
    parameter s6 = 6, s7 = 7, s8 = 8, s9 = 9; 
    // s3 = 3, s4 = 4, s5 = 5; 

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0) state <= Idle;
        else state <= nstate;
    end

    always @(*) begin
        case (state)
            Idle: nstate = a ? Idle : s1;
            s1  : nstate = a ? s2 : Idle;
            s2  : nstate = a ? s3 : Idle;
            s3  : nstate = s4;
            s4 : nstate = s5;
            s5 : nstate = s6;
            s6 : nstate = a ? s7 : Idle;
            s7 : nstate = a ? s8 : Idle;
            s8 : nstate = a == 1'b1 ? Idle : s9;
            s9 : nstate = Idle;
            default : nstate = Idle;
        endcase
    end

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0) match <= 0;
        else if (state == s9) match <= 1'b1;
        else match <= 1'b0;
    end

endmodule
```

移位寄存器法：

```verilog
`timescale 1ns/1ns
module sequence_detect(
    input clk,
    input rst_n,
    input a,
    output reg match
    );

    reg [8:0] memo;

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0)
            memo <= 0;
        else
            memo <= {memo[7:0], a};
    end

    wire prematch = memo[8:6] == 3'b011 && memo[2:0] == 3'b110;

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0)
            match <= 0;
        else
            match <= prematch;
    end

endmodule
```

## VL27 不重叠序列检测

```verilog
`timescale 1ns/1ns
module sequence_detect(
    input clk,
    input rst_n,
    input data,
    output reg match,
    output reg not_match
    );

    reg [5:0] buffer;
    reg [2:0] cnt;
    wire cntdown = cnt == 3'd5;

    always @(posedge clk or negedge rst_n ) begin
        if (rst_n  == 1'b0) cnt <= 0;
        else if (cntdown) cnt <= 0;
        else cnt <= cnt + 1'b1;
    end

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0) buffer <= 0;
        else buffer <= {buffer[4:0], data};
    end

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0) {match, not_match} <= 0;
        else if (cntdown && buffer == 6'b0011_10 && data == 1'b0)
            {match, not_match} <= 2'b10;
        else if (cntdown)
            {match, not_match} <= 2'b01;
        else
            {match, not_match} <= 2'b00;
    end
endmodule
```

## VL28 输入序列不连续的序列检测

```verilog
`timescale 1ns/1ns
module sequence_detect(
    input clk,
    input rst_n,
    input data,
    input data_valid,
    output reg match
    );

    reg [3:0] buffer;
    reg [1:0] cnt;
    wire cntdown = cnt == 2'b11;

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0) buffer <= 0;
        else if (data_valid) buffer <= {buffer[2:0], data};
// 注意题目要求的是序列不连续的检测
        else buffer <= 0;
    end

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0) cnt <= 0;
        else if (data_valid && !cntdown) cnt <= cnt + 1'b1;
        else cnt <= 0;
    end

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0) match <= 1'b0;
// 这个奇奇怪怪的判断条件也是无奈之举，时序图是这样安排的
        else if (data_valid && cntdown && buffer[2:0] == 3'b011 && data == 1'b0)
            match <= 1'b1;
        else
            match <= 1'b0;
    end

endmodule
```
