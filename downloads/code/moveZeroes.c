void moveZeroes(int* nums, int numsSize){
    int i = -1;  // point zero
    int j = 0;   // point non zero
    
    // find first zero
    while ( j < numsSize ) {
        if ( nums[j] == 0 ) {
            i = j;
            break;
        }
        ++j;
    }
    
    // zero not found or fist zero locates at last position
    if ( i < 0 || i == numsSize - 1 ) return;
    
    while ( j < numsSize ) {
        if ( nums[j] != 0 ) {
            nums[i] = nums[j];
            nums[j] = 0;
            i++;
        }
        j++;
    }  
}