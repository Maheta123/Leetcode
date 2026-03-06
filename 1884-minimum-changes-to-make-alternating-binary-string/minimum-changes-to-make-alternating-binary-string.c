int minOperations(char* s) {
    int n, c = 0, j = 0;
    for(n = 0; s[n] != '\0'; n++, j ^= 1) {
        if(s[n] - '0' == j) c++;
    }
    return fmin(c, n - c);
}