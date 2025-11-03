#define MAX(a,b) (a > b ? a : b)
int minCost(char* colors, int* neededTime, int neededTimeSize) {
    int ans = 0, max_time = neededTime[0], sum_time = neededTime[0];
    for(int i = 1; i < neededTimeSize; i++) {
        if(colors[i] != colors[i - 1]) {
            ans += sum_time - max_time;
            max_time = 0;
            sum_time = 0;
        }
        max_time = MAX(max_time, neededTime[i]);
        sum_time += neededTime[i];
    }
    ans += sum_time - max_time;
    return ans;
}