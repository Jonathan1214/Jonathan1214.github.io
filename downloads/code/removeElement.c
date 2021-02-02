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