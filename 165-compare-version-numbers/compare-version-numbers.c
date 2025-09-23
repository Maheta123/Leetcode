#pragma GCC optimize("O3", "unroll-loops")
int compareVersion(char* v1, char* v2) {
    const char* dot = ".";
    char *token1, *token2;
//    char *ptr1, *ptr2;
    while(token1 != NULL || token2 != NULL){
        token1 = strsep(&v1, dot);
        token2 = strsep(&v2, dot);
        int x1 = (token1 && *token1) ? atoi(token1) : 0;
        int x2 = (token2 && *token2) ? atoi(token2) : 0;
        if (x1 <x2) return -1;
        else if (x1 > x2) return 1;
    }
    return 0;
}