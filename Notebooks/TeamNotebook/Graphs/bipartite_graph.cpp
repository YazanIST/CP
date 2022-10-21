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