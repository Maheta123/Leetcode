#define COUNTS_SIZE 10

int counts[COUNTS_SIZE];

bool is_numerically_balanced(int n) {
    memset(counts, 0, sizeof(counts));
    while (n > 0) {
        counts[n % 10]++;
        n /= 10;
    }
    for (int i = 0; i < COUNTS_SIZE; i++) {
        if (counts[i] != 0 && counts[i] != i) {
            return false;
        }
    }
    return true;
}

int nextBeautifulNumber(int n) {
    while (!is_numerically_balanced(++n));
    return n;
}