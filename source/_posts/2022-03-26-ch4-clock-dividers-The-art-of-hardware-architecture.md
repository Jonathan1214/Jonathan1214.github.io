---
title: ch4-clock-dividers-The-art-of-hardware-architecture
copyright: true
notshow: true
tags:
  - TAHA
  - IC
  - 时钟
date: 2022-03-26 14:50:30
updated:
categories:
---

偶数分频时钟，奇数分频甚至是小数分频也在考虑范围内。

## 4.2 同步整数分频器

使用 Moore 状态机很容易实现同步整数分频。但是无法实现占空比 50% 的奇数分频。

![image-20220326145407841](D:\Documents\Jonathan1214.github.io\source\_drafts\ch4-clock-dividers-The-art-of-hardware-architecture\image-20220326145407841.png)

## 4.3 具有 50% 占空比的奇数整数分频

如下图所示，一个三分频，50% 占空比的例子。

![image-20220326145838377](D:\Documents\Jonathan1214.github.io\source\_drafts\ch4-clock-dividers-The-art-of-hardware-architecture\image-20220326145838377.png)

+ 计数 `0` 到 `N - 1`
+ 在 `0` 和 `(N+1)/2` 上生成使能信号
+ 分别在两个使能信号上用上升沿和下降沿做 T 触发器，将得到的结果异或即可

```verilog
module div3(
    input clk,
    input rst_n,
    output div3
);
    reg [1:0] cnt;
    wire tff_1en;
    wire tff_2en;
    reg div1;
    reg div2;

    assign tff_1en = cnt == 2'd0;
    assign tff_2en = cnt == 2'd2;
    assign div3 = div1 ^ div2;

    always @(posedge clk or negedge rst_n) begin
        if (rst_nn == 1'b0)
            cnt <= 0;
        else if (cnt == 2'd2)
            cnt <= 0;
        else
            cnt <= cnt + 1'b1;
    end

    always @(posedge clk or negedge rst_n) begin
        if (rst_n == 1'b0)
            div1 <= 0;
        else if (tff_1en)
            div1 <= ~div1;
    end

    always @(negedge clk or negedge rst_n) begin
        if (rst_n == 1'b0)
            div2 <= 0;
        else if (tff_2en)
            div2 <= ~div2;
    end

endmodule
```

## 4.4 非整数分频（非50%占空比）

这里以 1.5 分频为例，也就是没三个时钟包含两个对称的脉冲。

借助三分频器的辅助，用如下电路可以实现 1.5 分频：

![image-20220326151453897](D:\Documents\Jonathan1214.github.io\source\_drafts\ch4-clock-dividers-The-art-of-hardware-architecture\image-20220326151453897.png)

该电路容易出现毛刺，因为多路器的输入经历了不同的延迟，因此会出现这种情况。

### 分频计数器的实现

+ 使用复位值 `000000001` 的 9 位移位寄存器，可以在每个时钟上升沿使移位寄存器循环左移一位。
+ 产生第一个脉冲，在半周期时移动第 1 位并将第 1 位与第 2 位进行或操作。
+ 产生第二个脉冲，第 5 位和第 6 位必须在半周期时移动并与原始第 6 位进行或操作。

## 4.5 N 分频的替换方法

![image-20220326153413988](D:\Documents\Jonathan1214.github.io\source\_drafts\ch4-clock-dividers-The-art-of-hardware-architecture\image-20220326153413988.png)
