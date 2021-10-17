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