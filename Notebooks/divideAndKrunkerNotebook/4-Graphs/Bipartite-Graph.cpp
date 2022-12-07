const int N = 2e5 + 5;  

/* 
 * Problem statement:
 * There are n pupils in Uolevi's class, and m friendships between them. Your task
 * is to divide the pupils into two teams in such a way that no two pupils in a team
 * are friends. You can freely choose the sizes of the teams.
*/
 
int n, m, nodeTeam[N];
vector<int> grid[N];

void BFS(int src) {
    queue<int> q;
    q.push(src);
    nodeTeam[src] = 1;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for(auto x : grid[u]){
            if(!nodeTeam[x]) {
                if(nodeTeam[u] == 1) nodeTeam[x] = 2;
                else nodeTeam[x] = 1;
                q.push(x);
            }
            else if(nodeTeam[x] == nodeTeam[u]) {
                cout << "IMPOSSIBLE\n";
                exit(0);
            }
        }
    }
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        grid[a].push_back(b);
        grid[b].push_back(a);
    }
 
    for(int i = 1; i <= n; i++){
        if(!nodeTeam[i]) BFS(i);
    }
 
    for(int i = 1; i <= n; i++) {
        cout << nodeTeam[i] << ' '; 
    }
}