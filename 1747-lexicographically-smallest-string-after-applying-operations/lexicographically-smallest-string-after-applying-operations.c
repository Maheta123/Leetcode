#include <stdio.h>
#include <string.h>

#define MAXN 105

int gcd_int(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void add_digits_times(char *s, int add_times, int a, int start) {
    int n = strlen(s);
    int inc = (add_times * a) % 10;
    if (inc == 0) return;
    for (int i = start; i < n; i += 2) {
        int d = (s[i] - '0' + inc) % 10;
        s[i] = '0' + d;
    }
}

void rotate_right_by(char *s, int rot, char *out) {
    int n = strlen(s);
    if (n == 0) { out[0] = '\0'; return; }
    rot %= n;
    for (int i = 0; i < n; i++) {
        out[i] = s[(i - rot + n) % n];
    }
    out[n] = '\0';
}

char* findLexSmallestString(char* s, int a, int b) {
    static char ans[MAXN];
    strcpy(ans, s);
    int n = strlen(s);
    int g = gcd_int(n, b);
    int cycle = n / g; 
    char rotated[MAXN], t1[MAXN], t2[MAXN];

    for (int k = 0, rot = 0; k < cycle; k++, rot = (rot + b) % n) {
        rotate_right_by(s, rot, rotated);

        for (int cntOdd = 0; cntOdd < 10; cntOdd++) {
            strcpy(t1, rotated);
            add_digits_times(t1, cntOdd, a, 1); 

            if (b % 2 == 1) {
                for (int cntEven = 0; cntEven < 10; cntEven++) {
                    strcpy(t2, t1);
                    add_digits_times(t2, cntEven, a, 0); 
                    if (strcmp(t2, ans) < 0) strcpy(ans, t2);
                }
            } else {
                if (strcmp(t1, ans) < 0) strcpy(ans, t1);
            }
        }
    }

    return ans;
}