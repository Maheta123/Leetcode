int numWaterBottles(int numBottles, int numExchange) {
    int bottlesDrank = numBottles;

    while (numBottles >= numExchange) {
        int newBottles = numBottles / numExchange;
        bottlesDrank += newBottles;
        int leftover = numBottles % numExchange;
        numBottles = newBottles + leftover;
    }

    return bottlesDrank;
}