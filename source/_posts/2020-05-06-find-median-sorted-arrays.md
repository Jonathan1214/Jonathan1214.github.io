---
title: LeetCode | 4 两个排序数组的中位数
categories:
  - 学习
tags:
  - LeetCode
  - 算法
date: 2020-05-06 18:01:40
updated:
---


## 题目

给定两个大小为 `m` 和 `n` 的有序数组 `nums1` 和 `nums2`。找出这两个有序数组的中位数。要求算法的时间复杂度为`O(log(m+n))`。

### 示例

+ `nums1 = [1, 3]`，`nums2 = [2]`，中位数是 2.0；
+ `nums1 = [1, 2]`，`nums2 = [3, 4]`，中位数是 2.5；
<!-- more -->

## 题解

整体上是一个分而治之的思想，将问题分解，使用递归可以很方便的完成。这个问题是『寻找两个有序数组中的第 k 大元素』问题的特殊形式，我们直接实现寻址第 k 大元素的函数  `find_kth()` 即可，然后在 `findMedianSortedArrays()` 中调用它即可。

我们使用递归方式实现 `find_kth()`，对于递归算法，我们要注意递归终止条件。首先要确保第一个参数数组的长度是较短的，

+ 较短数组 `a` 的长度（未搜索区域长度）变为 0，返回 `b` 中第 `k` 个元素；
+ 待寻找的序数 `k = 1`，返回`a` 和 `b` 的第一个元素中的较小者。

然后我们需要确定每个数组的搜索长度。对于较小数组 `a`，搜索长度为数组长和 `k/2` 的较大者，余下的长度则为数组 `b` 待搜索的长度。

代码如下：

{% include_code LeetCodeSolution4.c lang:C %}