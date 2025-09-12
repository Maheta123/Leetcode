#include <stdbool.h>

bool doesAliceWin(const char *s) {
    for (; *s; ++s) {
        char c = *s;
        if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u')
            return true;
    }
    return false;
}