---
title: 从数组中删除元素
date: 2021-01-16 09:55:59
updated:
copyright: true
categories:
  - [学习, 算法]
tags:
  - 数组
  - 算法
  - LeetCode
---

接着上一篇 {% post_link inserting-items-into-an-array '向数组中插入元素' %} 而来，下面这两道题是从数组中删除删除元素，解法一样：[Remove Element](https://leetcode.com/problems/remove-element/) 和 [Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)。我还是太菜了，居然做不出来……看了 solution 之后才恍然大悟，原来如此，我把两个指针一前一后放置，然后向中间靠拢，但是后面那个指针的移动太快了，因此导致出错，真是『步子大了，喀嚓，容易扯着蛋』。

<!--more-->

> **Remove Element**：
>
> Given an array *nums* and a value `val`, remove all instances of that value [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) and return the new length. Do not allocate extra space for another array, you must do this by **modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** with `O(1)` extra memory. The order of elements can be changed. It doesn't matter what you leave beyond the new length.
>
> *example*：
>
> ```
> Input: nums = [3,2,2,3], val = 3
> Output: 2, nums = [2,2]
> Explanation: Your function should return length = 2, with the first two elements of nums being 2.
> It doesn't matter what you leave beyond the returned length. For example if you return 2 with nums = [2,2,3,3] or nums = [2,2,0,0], your answer will be accepted.
> ```
>
> **Remove Duplicates from Sorted Array**：
>
> Given a sorted array *nums*, remove the duplicates [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) such that each element appears only *once* and returns the new length. Do not allocate extra space for another array, you must do this by **modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** with O(1) extra memory.
>
> *example*：
>
> ```
> Input: nums = [1,1,2]
> Output: 2, nums = [1,2]
> Explanation: Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the returned length.
> ```
> 

题解如下所示：

```c
int removeElement(int* nums, int numsSize, int val){
    int i      = 0;
    int j      = numsSize - 1;
    while ( i <= j ) {
        // while ( nums[j] == val ) j--;
        if ( nums[i] == val ) {
            nums[i] = nums[j];
            j--;
        } else
            i++;
    }
    return j+1;
}
```

```c
int removeDuplicates(int* nums, int numsSize){
    if ( numsSize == 0 ) return 0;
    int j = 0;
    int n = 0;
    int curVal = nums[j];
    while ( j < numsSize - 1 ) {
        if ( nums[j+1] != curVal ) {
            nums[n++] = curVal;
            curVal = nums[j+1];
        }
        j++;
    }
    nums[n++] = curVal;
    return n;
}
```




