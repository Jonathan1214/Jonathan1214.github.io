---
title: 在数组中查找元素
date: 2021-01-17 09:45:29
updated:
categories:
  - [学习, 算法]
tags:
  - 数组
  - 算法
  - LeetCode
---

两道题都是在数组中查找元素，[Check If N and Its Double Exist](https://leetcode.com/problems/check-if-n-and-its-double-exist/)，[Valid Mountain Array](https://leetcode.com/problems/valid-mountain-array/)。问题的关键在于，在一个无序数组中查找，一般而言时间复杂度会达到 $O(n^2)$，比如第一题，看起来只能先排序一遍，然后使用二分搜索等查找方法才能把复杂度降下来，这里不给题解了，用 C 解的话还要自己写排序，看来后续要切换到用 C++ 解才行。第二题比较简单，边界条件也很好处理。

<!--more-->

> **Check If N and Its Double Exist**:
>
> Given an array `arr` of integers, check if there exists two integers `N` and `M` such that `N` is the double of `M` ( i.e. `N = 2 * M`). More formally check if there exists two indices `i` and `j` such that :
>
> + `i != j`
> + `0 <= i, j < arr.length`
> + `arr[i] == 2 * arr[j]`
>
> *example*:
>
> ```
> Input: arr = [10,2,5,3]
> Output: true
> Explanation: N = 10 is the double of M = 5,that is, 10 = 2 * 5.
> ```
>
> **Valid Mountain Array**:
>
> Given an array of integers `arr`, return *`true` if and only if it is a valid mountain array*. Recall that arr is a mountain array if and only if:
>
> - `arr.length >= 3`
>
> - There exists some `i` with `0 < i < arr.length - 1` such that:
>
>   - `arr[0] < arr[1] < ... < arr[i - 1] < arr[i]`
>   - `arr[i] > arr[i + 1] > ... > arr[arr.length - 1]`
>
>  *example*:
>
> ```
> Input: arr = [2,1]
> Output: false
> 
> Input: arr = [3,5,5]
> Output: false
> ```

`Valid Mountain Array` solution:

```c
bool validMountainArray(int* arr, int arrSize){
    if ( arrSize <= 2 ) return false;
    
    int i = 0;
    
    // find mountain
    while ( i < arrSize - 1 && arr[i] < arr[i+1] ) i++;
    if ( i == 0 || i == arrSize - 1) return false;
    
    while ( i < arrSize - 1 && arr[i] > arr[i+1] ) i++;
    
    if ( i == arrSize - 1) return true;
    else                   return false;
}
```



