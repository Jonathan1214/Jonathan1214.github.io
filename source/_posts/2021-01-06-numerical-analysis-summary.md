---
title: 数值分析总结
date: 2021-01-06 10:46:09
updated:
mathjax: true
categories:
  - 学习
tags:
  - notes
---

今天是 1 月 6 号，两天后将进行数值分析考试，那是本学期的最后一门考试课（研究生课），也是我本科参加的最后一门考试了。这几天好好复习了一下，虽然老师上课讲的好像比较复杂，比较难，但真要考起来也不会太难，往年的考试题也比较简单，心里有底了。写个简单的知识点总结吧，就当是消磨时间了，剩下这一两天也怪难熬的。

<!--more-->

总共分为 5 个部分：

+ 非线性方程和方程组的数值解法
+ 线性方程组的数值解法
+ 插值法和数值逼近
+ 数值积分
+ 常微分方程的初值问题和数值解法

以及一个额外的问题：乘幂法求矩阵的最大模特征值及对应的特征向量。

先从整体上来认识一下这门课程。数值分析，这个标题告诉我们这门课程就是要用一些数值方法去去近似求解一下难以求解的问题，这些问题往往是我们得不到解析解的，或者说只需要求出几个点的值而去求出整体的解析解没有多大意义，比如常第5部分会涉及到的常微分方程的初值问题。那么针对这些不同的问题，有哪些数值方法可以进行求解呢？

## 非线性方程和方程组的数值解法

非线性方程和方程组，这无疑是我们最常遇到的难以求得解析解的问题，针对这类问题，有一些很好的迭代算法可以用于求解。对于非线性方程的求解，最简单的数值求解方法就是二分法，更高级一点的方法有牛顿法以及其改进形式。

假设待求解的非线性方程是 $f(x) = 0$，迭代的第一步就是要通过这个方程构造出迭代形式：
$$
x_{k+1} = \phi(x_{k})
$$
其中，$\phi(x)$ 被称为迭代函数，迭代格式好不好就和这个迭代函数的性质有很大的关系。

收敛阶：满足如下条件，则称迭代格式 p 阶收敛，其中 $\epsilon_{i}$ 为第 i 次迭代的误差。
$$
\rm{lim}\frac{|\epsilon_{i+1}|}{|\epsilon_{i}|}=c \ne 0
$$


计算效率：$EI = p^{\frac{1}{\theta}}$。

局部收敛性：若 $\phi(x)$ 在 $x = \phi(x)$ 的根 $\alpha$ 的邻域内有连续的一阶导数，且满足 $|\phi^{'}(\alpha)| < 1$，则称 $x_{k+1} = \phi(x_{k})$ 具有局部收敛性。而且我们可以推出，$\alpha$ 处的导数模值越小，迭代收敛越快，显然当它为零的时候，收敛最快，由此我们可以引出另外一个关于收敛阶的定理：$x=\phi(x)$ 的根 $\alpha$ 邻域内有充分多阶连续导数，则关于 $\alpha$ p 阶收敛等价于 $\phi(x)$ 在 $\alpha$ 处的前 p-1 阶导数值全都为0，且 p 阶导数不为0。

了解了这些基础，对于二分法和牛顿法自然就是水到渠成的事情了。

对于非线性方程组，我们也有相应的拟牛顿法进行计算，这都不是什么难事儿，只是在多元问题中，导数值的计算变成了 Jacobi 矩阵的计算。

## 线性方程组的数值解法

再来看看线性方程组的数值解法。对一个线性方程组而言，当他满秩的时候

## 插值法和数值逼近

## 数值积分

## 常微分方程的初值问题和数值解法