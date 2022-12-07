/*
Convex Hull OPT
You are given n rectangles with vertexes in (0,0), (xi,0), (xi,yi), (0,yi). For each rectangle, you are also given a number ai. Choose some of them that the area of union minus sum of ai of the chosen ones is maximum.
It is guaranteed that there are no nested rectangles.
Nut has no idea how to find the answer, so he asked for your help.
*/
int main() {
    int n;
    cin >> n;
    vector<Rectangle> rectangles(n);
    for (auto &[x, y, a]: rectangles) {
        cin >> x >> y >> a;
    }
    sort(rectangles.begin(), rectangles.end());
    // dp[i] = the max area we can get that involves the
        // ith rectangle with some subset of rectangles before it
    // dp[i] = max(dp[j] + xi * yi - intersection(yi * xj) - ai, self)
    // this is correct because there are no nested rectangles
        // (x is increasing and y is decreasing after sorting by x)
    DynamicHull<ll> dynamicHull;
    ll dp = 0, ans = 0;
    dynamicHull.insert_line(0, 0);
    for (int i = 0; i < n; i++) {
        dp = dynamicHull.eval(rectangles[i].y) + rectangles[i].x * rectangles[i].y - rectangles[i].a;
        dynamicHull.insert_line(-rectangles[i].x, dp);
        ans = max(ans, dp);
    }
    cout << ans;
}