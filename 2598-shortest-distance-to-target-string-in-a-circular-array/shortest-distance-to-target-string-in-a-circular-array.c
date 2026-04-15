int closestTarget(char** words, int wordsSize, char* target, int startIndex) {
    bool d = true;
    for(int i = 0; i < wordsSize; i++){
        if(strcmp(words[i], target) == 0) {
            d = false;
            break;
        }
    }
    if(d) {
        return -1;
    }
    int x = startIndex;
    int y = startIndex;
    int xCount = 0;
    int yCount = 0;
    while (true) {
        if(strcmp(words[x], target) != 0) {
            x--;
            if(x == -1) {
                x = wordsSize - 1;
            }
            xCount++;
        } else {
            break;
        }
    }
    while (true) {
        if(strcmp(words[y], target) != 0) {
            y++;
            if(y == wordsSize) {
                y = 0;
            }
            yCount++;
        } else {
            break;
        }
    }
    if(xCount < yCount) {
        return xCount;
    }
    return yCount;
}