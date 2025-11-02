int strStr(char* haystack, char* needle) {
    int n= strlen(haystack),s=strlen(needle);
    int i,j;

    if (s == 0) return 0; 

    for(i=0;i<=n;i++){
        for (j = 0; j < s; j++) {
            if (haystack[i + j] != needle[j]) break;
        }
        if(j==s) return i;
    }

    return -1;

}