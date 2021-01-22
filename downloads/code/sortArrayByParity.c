int* sortArrayByParity(int* A, int ASize, int* returnSize){
    *returnSize = ASize;
    if ( ASize < 1 ) return A;

    int i = 0;
    int j = ASize - 1;
    int tmp;

    // iterate until i == j
    while ( i < j ) {
        while ( i < ASize-1 && A[i] % 2 == 0 ) // even
            i++;
        while ( j >= 0 && A[j] % 2 ) // odd
            j--;
        if ( i < j ) { // swap
            tmp    = A[i];
            A[i++] = A[j];
            A[j--] =tmp;
        } else
            break;
    }
    return A;
}