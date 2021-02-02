int* replaceElements(int* arr, int arrSize, int* returnSize){
    *returnSize = arrSize;

    // iterate from end
    // since arr.length is greater than 0
    if ( arrSize < 1 ) return arr;

    int r_max = arr[arrSize-1]; // tmp max
    arr[arrSize-1] = -1;        // last value ===> -1
    int tmp;

    int i     = arrSize - 2;        // iterate from second to last
    while ( i >= 0 ) {              // iterate until first value
        tmp     = arr[i];
        arr[i]  = r_max;
        r_max   = (tmp > r_max) ? tmp : r_max;
        i--;
    }
    return arr;
}