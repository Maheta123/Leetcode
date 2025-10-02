int maxBottlesDrunk(int numBottles, int numExchange) {
    int ans = numBottles;
    int empty = numBottles;

    while (empty >= numExchange) {
        empty -= numExchange;
        numExchange += 1;
        ans += 1;
        empty += 1;
    }
    return ans;
}