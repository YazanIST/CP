// There are n children and m apples that will be distributed to them. Your task is to count the number of ways this can be done.
// For example, if n=3 and m=2, there are 6 ways: [0,0,2], [0,1,1], [0,2,0], [1,0,1], [1,1,0] and [2,0,0].
int main(){
    calcFact();
    int k,n;
    cin>>k>>n;
    // using Stars and bars theorem
    cout<<nCk(n+k-1,n);
}