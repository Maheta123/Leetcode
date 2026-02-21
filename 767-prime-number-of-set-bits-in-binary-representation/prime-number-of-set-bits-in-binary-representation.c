int countPrimeSetBits(int left, int right) {
    int numCount = 0;
    for(int num = left; num <= right; num++) {
        int bitCount = __builtin_popcount(num);
        if(
            bitCount == 2 ||
            bitCount == 3 ||
            bitCount == 5 ||   
            bitCount == 7 ||
            bitCount == 11 ||
            bitCount == 13 ||
            bitCount == 17 ||
            bitCount == 19
        ) {
            numCount++;
        }
    }
    return numCount;
}