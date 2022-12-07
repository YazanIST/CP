// Given an array of n integers, your task is to calculate the number of increasing subsequences it contains. If two subsequences have the same values but in different positions in the array, they are counted separately.
int main(){
    int n;
    cin>>n;
    vector<int>a(n),comp;
    for(auto &x:a){
        cin>>x;
        comp.push_back(x);
    }
    sort(comp.begin(),comp.end());
    comp.resize(unique(comp.begin(),comp.end())-comp.begin());
    for(auto &x:a){
        x=lower_bound(comp.begin(),comp.end(),x)-comp.begin()+1;
    }
    SegmentTree segtree(n);
    int ans=0;
    for(int i=0;i<n;i++){
        ans=add(ans,add(segtree.get(0,a[i]-1),1));
        segtree.update(a[i],add(segtree.get(a[i],a[i]),add(segtree.get(0,a[i]-1),1)));
    }
    cout<<ans;
}