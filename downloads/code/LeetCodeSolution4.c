// 辅助函数 选择两个有序数组中第 k 大的数
int find_kth(int *a, int alen, int *b, int blen, int k)
{
    // 确保 alen < blen
    if (alen > blen)
        return find_kth(b, blen, a, alen, k);
    if (alen == 0)
        return b[k-1];
    if (k == 1)
        return a[0] < b[0] ? a[0] : b[0];

    int ia = alen > k/2 ? k/2 : alen;
    int ib = k - ia;

    if (b[ib-1] > a[ia-1])
        return find_kth(a+ia, alen-ia, b, blen, k-ia);
    else if (b[ib-1] < a[ia-1])
        return find_kth(a, alen, b+ib, blen-ib, k-ib);
    else // 注意这种情况
        return a[ia-1];
}
// 找出两个有序数组中的中位数
double findMedianSortedArrays(int *nums1, int nums1Size,
                        int *nums2, int nums2Size)
{
    int mid = nums2Size + (nums1Size - nums2Size) / 2;
    // if ((nums1Size & 0x1) ^ (nums2Size & 0x1)) // 和为奇数
    if ((nums1Size+nums2Size) & 0x1)
        return find_kth(nums1, nums1Size, nums2, nums2Size, mid+1);
    else    // 和为偶数
        return (find_kth(nums1, nums1Size, nums2, nums2Size, mid)
                    + find_kth(nums1, nums1Size, nums2, nums2Size, mid+1)) / 2.0;
}