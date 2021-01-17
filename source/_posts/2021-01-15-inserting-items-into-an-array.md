---
title: 向数组中插入数据
date: 2021-01-15 21:15:23
updated:
categories:
  - [学习, 算法]
tags:
  - 数组
  - 算法
  - LeetCode
---

今天就不写记录了，来写下今天做的两道题：[duplicate zeros](https://leetcode.com/problems/duplicate-zeros/)，[merge sorted array](https://leetcode.com/problems/merge-sorted-array/)，均来自 Array101 模块。

在写之前，我得反省下，做这两道题花的时间实在是太长了，这直接导致下午做毕设计划的失败，今天又是没做毕设的一天。已经是周五了，下周一需要和老师约一次讨论，后面两天抓紧点完成。为了控制自己去做不想做的事情，希望做到下面这些：刷题就给自己 15mins，做不出来就不要再想了，继续想下午八成也是做不出来的，不如直接看看答案的思路，好好学习下；别打游戏了……

<!--more-->

先来看两道题的描述：

> **Duplicate Zeros**：
>
> Given a fixed length array `arr` of integers, duplicate each occurrence of zero, shifting the remaining elements to the right. Note that elements beyond the length of the original array are not written. Do the above modifications to the input array **in place**, do not return anything from your function.
>
> *example*：
>
> ```
> Input: [1,0,2,3,0,4,5,0]
> Output: null
> Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
> 
> Input: [1,2,3]
> Output: null
> Explanation: After calling your function, the input array is modified to: [1,2,3]
> ```
>
> **Merge Sorted Array**：
>
> Given two sorted integer arrays `nums1` and `nums2`, merge `nums2` into `nums1` as one sorted array. The number of elements initialized in `nums1` and `nums2` are `m` and `n` respectively. You may assume that `nums1` has enough space (size that is equal to `m + n`) to hold additional elements from `nums2`.
>
> *example*：
>
> ```
> Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
> Output: [1,2,2,3,5,6]
> 
> Input: nums1 = [1], m = 1, nums2 = [], n = 0
> Output: [1]
> ```

显然，这两道题是类似的，且第二道更简单，不过在看题解之前，我实在是想不出来该如何解决问题，知道看了题解才恍然大悟：原来我一直想的都是从前到后遍历数组，以期待解决问题，但未曾想到这两道题应该从后向前思考……

以 duplicate zeros 为例，`O(n^2)` 的方法很容易想到：遍历数组，每当当前值为0，复制值到下一个位置，然后将所有的值都向后推。我们这里不考虑这种暴力解法。为了达成将数组中的 0 向后复制一个位置，且多出的数直接向后推出数组，如果从前向后考虑，那么向后迭代时我们需要保存好当前的值，还要根据下一个位置的值是否为 0 进行不同的操作，这里面的条件实在太多了，很难判断。如果从后向前考虑就不一样了，假设已经操作结束了，那么有相当一部分值被推出了数组，这不是是意味着原来他们所在的空间在迭代的时候是可以被使用的，如 example 中的 5，他位于数组的第7个位，在迭代时我们根本不用管这个数，假装他不存在就好了。为了达到这个目的，我们需要先遍历一遍数组，计算有多个 0 要被复制，这样我们就知道后几个值会被推出数组，然后再从后往前遍历，将他们依次尽可能的往数组末尾推，这样就完成了整个算法，当然其中有一些边界条件很烦人，需要细心处理。最终的代码如下：

```c
void duplicateZeros(int* arr, int arrSize){
    int i;
    int zeros_cnt = 0;
    int copy_from;
    int copy_to;

    // count how many zeros in array
    for ( i = 0; i < arrSize; i++ ) {
        if ( i + zeros_cnt < arrSize ) {
            if ( arr[i] == 0)
                zeros_cnt++;
        } else
            break;
    }
    int tmp = i + zeros_cnt;
    if ( zeros_cnt > 0 && (tmp > arrSize )) zeros_cnt--;

    copy_from = arrSize - zeros_cnt - 1;
    copy_to   = arrSize - 1;
    // zeros at boundary, copy directly
    if ( arr[copy_from] == 0 && (tmp > arrSize) )
        arr[copy_to--] = arr[copy_from--];
    // exchange from end
    while ( copy_from >= 0 ) {
        if ( arr[copy_from] == 0 ) {
            arr[copy_to]   = 0;
            arr[copy_to-1] = 0;
            copy_to -= 2;
            copy_from--;
        } else {
            arr[copy_to--] = arr[copy_from--];
        }
    }
}
```

后面那道和前面的非常相似，为什么说更加简单？因为只需要从后往前向数组内写入两个数组当前值中的最小值即可，没有前面那道题中那么 tricky 的边界条件。最终的代码如下：

```c
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    int i   = m + n - 1;
    int p_1 = m - 1;
    int p_2 = n - 1;
    int curVal;
    while ( p_2 >= 0 && p_1 >= 0 )
        nums1[i--] = (nums2[p_2] > nums1[p_1]) ? nums2[p_2--] : nums1[p_1--];
    
    while ( p_2 >= 0 )
        nums1[i--] = nums2[p_2--];
}
```

简单总结下，当问题从前向后难以解决时，不妨假设问题已经解决了，基于解决后的情形试试从后往前处理。

