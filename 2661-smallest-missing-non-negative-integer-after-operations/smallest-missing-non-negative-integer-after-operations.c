int findSmallestInteger(int* nums, int numsSize, int value) {
    int* remSeen = (int*)calloc(value, sizeof(int));

    for(int i = 0; i < numsSize; i++){
        int rem = ((nums[i] % value) + value) % value;
        remSeen[rem]++;
    }

    int mex = 0;
    while(remSeen[mex % value]){
        remSeen[mex % value]--;
        mex++;
    }

    free(remSeen);
    return mex;
}