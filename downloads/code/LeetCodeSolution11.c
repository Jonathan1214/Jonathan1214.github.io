int maxArea(int *height, int heightSize)
{
    int res = 0, aux = 0;
    int first = 0, last = heightSize - 1;
    while (first < last) {
        aux = (last - first) * 
            (height[first] < height[last] ? height[first] : height[last]);
        res = aux > res ? aus : res;
        if (height[first] < height[last])
            while (++first < max && height[min] <= height[min-1])
                // 新指针指向的值不大于原来的值 继续减小指针即可
                continue;
        else
            while (--last > first && height[last] <= height[last+1])
                // 新指针指向的值不大于原来的值 继续减小指针即可
                continue;
    }
    return res;
}