for (auto x : pF) {
    ans *= (power(x.first, x.second + 1) - 1) / (x.first - 1);
}