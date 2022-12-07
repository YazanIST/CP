// 2D Binary Indexed Trees
const int N = 1000;
int BIT[N][N];
void updatey(int T, int idx, int val) {
    while (idx < N) {
        BIT[T][idx] += val;
        idx += idx & -idx;
    }
}
// update point
void update(int x, int y, int val) {
    while (x < N) {
        updatey(x, y, val);
        x += x & -x;
    }
}
int gety(int T, int idx) {
    int res = 0;
    while (idx != 0) {
        res += BIT[T][idx];
        idx -= idx & -idx;
    }
    return res;
}
// get value in rectangle (0 , 0), (x , y)
int get(int x, int y) {
    int res = 0;
    while (x != 0) {
        res += gety(x, y);
        x -= x & -x;
    }
    return res;
}