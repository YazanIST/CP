// modify for articulation points (from book)
function<void(int, int)>findBridges=[&](int v, int p)->void{
    dfsNum[v]=++dfsTime;
    dfsLow[v]=dfsNum[v];

    for(auto u:adj[v]){
        if(!dfsNum[u]){
            findBridges(u,v);
            dfsLow[v]=min(dfsLow[v],dfsLow[u]);
            if(dfsLow[u]>dfsNum[v]){
                brdiges[{u,v}]=brdiges[{v,u}]=true;
            }
        } else if(u!=p){
            dfsLow[v]=min(dfsLow[v],dfsNum[u]);
        }
    }
};
