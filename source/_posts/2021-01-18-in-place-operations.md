---
title: 原地操作
date: 2021-01-18 09:42:40
updated:
categories:
  - [学习, 算法]
tags:
  - 数组
  - 算法
  - LeetCode
---

数组相关算法中的原地操作，即空间复杂度位 $O(1)$，不需要开辟新的数组空间。一共是 5 道题：[ Replace Elements with Greatest Element on Right Side](https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/)，[Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)，[Move Zeroes](https://leetcode.com/problems/move-zeroes/)，[Sort Array By Parity](https://leetcode.com/problems/sort-array-by-parity/)，[Remove Element](https://leetcode.com/problems/remove-element/)。其中有两题之前做过了，参考 {% post_link remove-item-from-an-array '从数组中删除元素' %}。

<!--more-->

> ## **Replace Elements with Greatest Element on Right Side**
>
> Given an array arr, replace every element in that array with the greatest element among the elements to its right, and replace the last element with -1. After doing so, return the array.
>
> *example*:
>
> ``` 
> Input: arr = [17,18,5,4,6,1]
> Output: [18,6,6,6,1,-1]
> Input: arr = [17,18,5,4,6,1]
> Output: [18,6,6,6,1,-1]
> ```
> solution：
> ```c
> int* replaceElements(int* arr, int arrSize, int* returnSize){
>  *returnSize = arrSize;
> 
>  // iterate from end
>  // since arr.length is greater than 0
>  if ( arrSize < 1 ) return arr;
> 
>  int r_max = arr[arrSize-1]; // tmp max
>  arr[arrSize-1] = -1;        // last value ===> -1
>  int tmp;
> 
>  int i     = arrSize - 2;        // iterate from second to last
>  while ( i >= 0 ) {              // iterate until first value
>      tmp     = arr[i];
>      arr[i]  = r_max;
>      r_max   = (tmp > r_max) ? tmp : r_max;
>      i--;
>  }
>  return arr;
> }
> ```

双指针是实现 in-place 操作的主要技巧： 

> This was just a very brief introduction to the very versatile and widely used **two-pointer technique**. It is one of the main techniques used for in-place Array algorithms. We'll be looking at it further in the next Array explore card!

> ## **Move Zeroes**:
>
> Given an array `nums`, write a function to move all `0`'s to the end of it while maintaining the relative order of the non-zero elements.
>
> *example*:
>
> ```
> Input: [0,1,0,3,12]
> Output: [1,3,12,0,0]
> ```
> solution:
> ```c
> void moveZeroes(int* nums, int numsSize){
>     int i = -1;  // point zero
>     int j = 0;   // point non zero
>     
>     // find first zero
>     while ( j < numsSize ) {
>         if ( nums[j] == 0 ) {
>             i = j;
>             break;
>         }
>         ++j;
>     }
>     
>     // zero not found or fist zero locates at last position
>     if ( i < 0 || i == numsSize - 1 ) return;
>     
>     while ( j < numsSize ) {
>         if ( nums[j] != 0 ) {
>             nums[i] = nums[j];
>             nums[j] = 0;
>             i++;
>         }
>         j++;
>     }  
> }
> ```

> ## **Sort Array By Parity**:
>
> Given an array `A` of non-negative integers, return an array consisting of all the even elements of `A`, followed by all the odd elements of `A`. You may return any answer array that satisfies this condition.
>
> example:
>
> ```
> Input: [3,1,2,4]
> Output: [2,4,3,1]
> The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
> ```
> solution:
>
> ```c
> void moveZeroes(int* nums, int numsSize){
>     int i = -1;  // point zero
>     int j = 0;   // point non zero
>     
>     // find first zero
>     while ( j < numsSize ) {
>         if ( nums[j] == 0 ) {
>             i = j;
>             break;
>         }
>         ++j;
>     }
>     
>     // zero not found or fist zero locates at last position
>     if ( i < 0 || i == numsSize - 1 ) return;
>     
>     while ( j < numsSize ) {
>         if ( nums[j] != 0 ) {
>             nums[i] = nums[j];
>             nums[j] = 0;
>             i++;
>         }
>         j++;
>     }  
> }
> ```