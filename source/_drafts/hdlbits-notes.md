---
title: hdlbits-notes
date: 2021-01-30 09:35:35
categories:
tags:
---

## Popcount255

[Popcount255](https://hdlbits.01xz.net/wiki/Popcount255)

A "population count" circuit counts the number of '1's in an input vector. Build a population count circuit for a 255-bit input vector.

```verilog
module top_module( 
    input [254:0] in,
    output [7:0] out );
	
    always @(*) begin
        out = 8'd0;
        for (integer i = 0; i < 255; i = i + 1) begin
            if ( in[i] == 1'b1 )
                out = out + 1'b1;
            else
                out = out + 1'b0;
        end
    end
endmodule
```

## Adder100i

[Adder100i](https://hdlbits.01xz.net/wiki/Adder100i)

Create a 100-bit binary ripple-carry adder by instantiating 100 [full adders](https://hdlbits.01xz.net/wiki/Fadd). The adder adds two 100-bit numbers and a carry-in to produce a 100-bit sum and carry out. To encourage you to actually instantiate full adders, also output the carry-out from *each* full adder in the ripple-carry adder. cout[99] is the final carry-out from the last full adder, and is the carry-out you usually see.

```verilog
module top_module( 
    input [99:0] a, b,
    input cin,
    output [99:0] cout,
    output [99:0] sum );
    
    always @(*) begin
        cout = 100'd0;
        sum = 100'd0;
        {cout[0], sum[0]} = a[0] + b[0] + cin;
        for (integer i = 1; i < 100; i = i + 1) begin
            {cout[i], sum[i]} = a[i] + b[i] + cout[i-1];
        end
    end
//    genvar i;
//    generate
//        for ( i = 0; i < 100; i = i + 1 ) begin : fulladder
//            
/        end
//    endgenerate
endmodule
```

## Bcdadd100

[Bcdadd100](https://hdlbits.01xz.net/wiki/Bcdadd100)

You are provided with a BCD one-digit adder named `bcd_fadd` that adds two BCD digits and carry-in, and produces a sum and carry-out.

```verilog
module bcd_fadd {
    input [3:0] a,
    input [3:0] b,
    input     cin,
    output   cout,
    output [3:0] sum );
```

Instantiate 100 copies of `bcd_fadd` to create a 100-digit BCD ripple-carry adder. Your adder should add two 100-digit BCD numbers (packed into 400-bit vectors) and a carry-in to produce a 100-digit sum and carry out.

```verilog
module top_module( 
    input [399:0] a, b,
    input cin,
    output cout,
    output [399:0] sum );
    
    wire [99:0] carry;
    bcd_fadd bcd_fadd_inst_0 (
        .a(a[3:0]),
        .b(b[3:0]),
        .cin(cin),
        .cout(carry[0]),
        .sum(sum[3:0])
    );
    
    genvar i;
    generate
        for ( i = 1; i < 100; i = i + 1 ) begin : bcd_fadd_inst
            bcd_fadd bcd_fadd_inst_0 (
                .a(a[4*i+3:4*i]),
                .b(b[4*i+3:4*i]),
                .cin(carry[i-1]),
                .cout(carry[i]),
                .sum(sum[4*i+3:4*i])
    		);
        end
    endgenerate
    
    assign cout = carry[99];

endmodule
```

## Ringer

[Ringer](https://hdlbits.01xz.net/wiki/Ringer)

Suppose you are designing a circuit to control a cellphone's ringer and vibration motor. Whenever the phone needs to ring from an incoming call (`input **ring**`), your circuit must either turn on the ringer (`output **ringer** = 1`) or the motor (`output **motor** = 1`), but not both. If the phone is in vibrate mode (`input **vibrate_mode** = 1`), turn on the motor. Otherwise, turn on the ringer.

Suppose you are designing a circuit to control a cellphone's ringer and vibration motor. Whenever the phone needs to ring from an incoming call (`input **ring**`), your circuit must either turn on the ringer (`output **ringer** = 1`) or the motor (`output **motor** = 1`), but not both. If the phone is in vibrate mode (`input **vibrate_mode** = 1`), turn on the motor. Otherwise, turn on the ringer.

Try to use only `assign` statements, to see whether you can translate a problem description into a collection of logic gates.

**Design hint:** When designing circuits, one often has to think of the problem "backwards", starting from the outputs then working backwards towards the inputs. This is often the opposite of how one would think about a (sequential, imperative) programming problem, where one would look at the inputs first then decide on an action (or output). For sequential programs, one would often think "If (inputs are ___ ) then (output should be ___ )". On the other hand, hardware designers often think "The (output should be ___ ) when (inputs are ___ )".

这段话真是很有意思啊，从输出端开始考虑，根据输出去撕开输入条件，每一个输出一条语句，这正能体现并行，这正是软件编程和硬件编程的区别，妙极！妙极！在做 CSAPP 的 datalab 实验时，我也体会到这种感觉，应该从输出倒推输入条件，这样才能方便用逻辑门去处理，真是太妙了。

The above problem description is written in an imperative form suitable for software programming (*if ring then do this*), so you must convert it to a more declarative form suitable for hardware implementation (`*assign ringer = ___*`). Being able to think in, and translate between, both styles is one of the most important skills needed for hardware design.

```verilog
module top_module (
    input ring,
    input vibrate_mode,
    output ringer,       // Make sound
    output motor         // Vibrate
);
    assign ringer = ring & (~vibrate_mode);
    assign motor = ring & vibrate_mode;
endmodule
```

## Gatesv100

[Gatesv100](https://hdlbits.01xz.net/wiki/Gatesv100)

You are given a 100-bit input vector in[99:0]. We want to know some relationships between each bit and its neighbour:

- **out_both**: Each bit of this output vector should indicate whether *both* the corresponding input bit and its neighbour to the **left** are '1'. For example, `out_both[98]` should indicate if `in[98]` and `in[99]` are both 1. Since `in[99]` has no neighbour to the left, the answer is obvious so we don't need to know `out_both[99]`.
- **out_any**: Each bit of this output vector should indicate whether *any* of the corresponding input bit and its neighbour to the **right** are '1'. For example, `out_any[2]` should indicate if either `in[2]` or `in[1]` are 1. Since `in[0]` has no neighbour to the right, the answer is obvious so we don't need to know `out_any[0]`.

- **out_different**: Each bit of this output vector should indicate whether the corresponding input bit is different from its neighbour to the **left**. For example, `out_different[98]` should indicate if `in[98]` is different from `in[99]`. For this part, treat the vector as wrapping around, so `in[99]`'s neighbour to the left is `in[0]`.

```verilog
module top_module( 
    input [99:0] in,
    output [98:0] out_both,
    output [99:1] out_any,
    output [99:0] out_different );
    
    assign out_both = in[98:0] & in[99:1];
    assign out_any = in[99:1] | in[98:0];
    assign out_different = {in[99] ^ in[0], in[98:0] ^ in[99:1]};
    
endmodule
```

## Mux256to1v

reate a 4-bit wide, 256-to-1 multiplexer. The 256 4-bit inputs are all packed into a single 1024-bit input vector. sel=0 should select bits `in[3:0]`, sel=1 selects bits `in[7:4]`, sel=2 selects bits `in[11:8]`, etc.

**Indexed vector part select**，感觉挺有意思的，可以去好好了解下。

*hint:*

- With this many options, a case statement isn't so useful.
- Vector indices can be variable, as long as the synthesizer can figure out that the width of the bits being selected is constant. It's not always good at this. An error saying "... is not a constant" means it couldn't prove that the select width is constant. In particular, `in[ sel*4+3 : sel*4 ]` does not work.
- Bit slicing ("Indexed vector part select", since Verilog-2001) has an even more compact syntax.

```verilog
module top_module( 
    input [1023:0] in,
    input [7:0] sel,
    output [3:0] out );
	
    assign out = in[sel*4+:4];
endmodule
```

