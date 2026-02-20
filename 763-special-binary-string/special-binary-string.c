int cmp(const void *a, const void *b) {
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;
    return strcmp(s2, s1); 
}

char* makeLargestSpecial(char* s) {
    int n = strlen(s);
    if (n <= 2) return strdup(s);

    char **subs = malloc(n * sizeof(char *));
    int count = 0;
    int balance = 0;
    int start = 0;

    for (int i = 0; i < n; i++) {
        balance += (s[i] == '1') ? 1 : -1;

        if (balance == 0) {
            int len = i - start + 1;

            char *inner = malloc(len - 1);
            strncpy(inner, s + start + 1, len - 2);
            inner[len - 2] = '\0';

            char *processed = makeLargestSpecial(inner);
            free(inner);

            char *full = malloc(len + 1);
            full[0] = '1';
            strcpy(full + 1, processed);
            full[len - 1] = '0';
            full[len] = '\0';

            free(processed);

            subs[count++] = full;
            start = i + 1;
        }
    }

    qsort(subs, count, sizeof(char *), cmp);

    char *result = malloc(n + 1);
    result[0] = '\0';

    for (int i = 0; i < count; i++) {
        strcat(result, subs[i]);
        free(subs[i]);
    }

    free(subs);

    return result;
}