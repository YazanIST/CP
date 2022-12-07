// There are n boys and m girls in a school. Next week a school dance will be organized. A dance pair consists of a boy and a girl, and there are k potential pairs.
// Your task is to find out the maximum number of dance pairs and show how this number can be achieved.
const int N = 501;
int n, m, k, vis_token = 1;
vector<int> adj[N], mt(N), vis(N);
bool try_kuhn(int v) {
    if (vis[v] == vis_token)
        return false;
    vis[v] = vis_token;
    for (auto to : adj[v]) {
        if (mt[to] == -1) {
            mt[to] = v;
            return true;
        }
    }
    for (auto to : adj[v]) {
        if (try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}
void solve() {
    cin >> n >> m >> k;
    while (k--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
    }
    int ans = 0;
    fill(mt.begin(), mt.end(), -1);
    for (int i = 0; i < n; i++) {
        vis_token++;
        ans += try_kuhn(i);
    }
    cout << ans << '\n';
    for (int i = 0; i < m; i++)
        if (mt[i] != -1)
            cout << mt[i] + 1 << ' ' << i + 1 << '\n';
}