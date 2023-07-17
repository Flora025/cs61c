int factorial(int n) {
    int res = 1;
    while (n > 0) {
        res = res * n;
        n--;
    }
    return res;
}