// There are n children and m apples that will be distributed to them.
// Your task is to count the number of ways this can be done.
calcFact();
int k, n;
cin >> k >> n;
// using Stars and bars theorem
cout << nCk(n + k - 1, n);