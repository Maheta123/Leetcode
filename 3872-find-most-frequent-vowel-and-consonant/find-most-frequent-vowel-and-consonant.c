int maxFreqSum(char* s) {
    int freq[256] = {0};
    int con = 0, vow = 0;
    for (int i = 0; s[i]; i++) {
        freq[(unsigned char)s[i]]++;
    }
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            if (strchr("aeiou", i)) {
                if (freq[i] > vow) vow = freq[i];
            } else {
                if (freq[i] > con) con = freq[i];
            }
        }
    }
    return con + vow;
}