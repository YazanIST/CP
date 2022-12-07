// You are given a rooted tree consisting of n nodes. The nodes are numbered 1,2,…,n, and node 1 is the root. Each node has a color.
// Your task is to determine for each node the number of distinct colors in the subtree of the node.
const int N = 2e5 + 1;
vector<int> adj[N];
int n, color[N], ans[N];
set<int> dis[N];
void calc(int v, int p) {
    for (auto u : adj[v]) {
        if (p == u) continue;
        calc(u, v);
        if (dis[v].size() < dis[u].size()) {
            swap(dis[v], dis[u]);
        }
        for (auto x : dis[u]) {
            dis[v].insert(x);
        }
    }
    ans[v] = dis[v].size();
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        dis[i].insert(x);
    }
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        v--, u--;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    calc(0, -1);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
}

// another on same idea
// You are given a rooted tree with root in vertex 1. Each vertex is coloured in some colour.
// Let's call colour c dominating in the subtree of vertex v if there are no other colours that appear in the subtree of vertex v more times than colour c. So it's possible that two or more colours will be dominating in the subtree of some vertex.
// The subtree of vertex v is the vertex v and all other vertices that contains vertex v in each path to the root.
// For each vertex v find the sum of all dominating colours in the subtree of vertex v.
const int N = 2e5 + 1;
int n;
vector<int> adj[N], color(N), mx(N, 1);
vector<ll> ans(N);
map<int, int> freq[N];
void calc(int v, int p) {
    freq[v][color[v]]++;
    mx[v] = 1;
    ans[v] = color[v];
    for (auto u : adj[v]) {
        if (u == p) continue;
        calc(u, v);
        if (freq[v].size() < freq[u].size()) {
            swap(freq[v], freq[u]);
            ans[v] = ans[u];
            mx[v] = mx[u];
        }
        for (auto x : freq[u]) {
            freq[v][x.first] += x.second;
            if (freq[v][x.first] > mx[v]) {
                mx[v] = freq[v][x.first];
                ans[v] = x.first;
            } else if (freq[v][x.first] == mx[v]) {
                ans[v] += x.first;
            }
        }
    }
}

// another
// A colorful tree is a tree in which each of its vertices has a specific color.
// A tedious path is a path in the tree such that both the initial and final vertices have the same color, and there is no vertex or edge that appear more than once in the path. Note that the color of the intermediate vertices, if there are any, are irrelevant.
// Given a colorful tree, with N vertices, your task is calculate, for each of the edges, the number of tedious paths that go through that edge.
int main() {
    int n;
    cin >> n;
    vector<int> color(n), freqAll(n);
    vector<vector<int>> adj(n);
    vector<pair<int, int>> edges;
    // read
    vector<int> dep(n);
    vector<ll> ans(n);
    vector<map<int, int>> freq(n);
    function<void(int, int)> calc = [&](int v, int p) {
        if (p != -1) {
            dep[v] = dep[p] + 1;
        }
        freq[v][color[v]]++;
        ans[v] = freqAll[color[v]] - 1;
        for (auto u: adj[v]) {
            if (u == p) continue;
            calc(u, v);
            if (freq[v].size() < freq[u].size()) {
                swap(freq[v], freq[u]);
                ans[v] = ans[u];
            }
            for (auto [col, colFreq]: freq[u]) {
                ans[v] -= freq[v][col] * (freqAll[col] - freq[v][col]);
                freq[v][col] += colFreq;
                ans[v] += freq[v][col] * (freqAll[col] - freq[v][col]);
            }
        }
    };
    calc(0, -1);
    for (auto [v, u]: edges) {
        if (dep[v] < dep[u]) swap(v, u);
        cout << ans[v] << ' ';
    }
}