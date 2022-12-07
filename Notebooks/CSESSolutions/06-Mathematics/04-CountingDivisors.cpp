// Given n integers, your task is to report for each integer the number of its divisors.
int div(int x) {
    int count = 0;
    for (int i = 1; i <= sqrt(x); i++) {
        if (x % i == 0) {
            if (x / i == i) count++;
            else count += 2;
        }
    }
    return count;
}