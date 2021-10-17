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