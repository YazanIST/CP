ll calc(int m, int n){
    ll p=1,k=1;
    if(m-n<n) n=m-n;
 
    if(n!=0){
        while(n){
            p*=m;
            k*=n;
            long long GCD=__gcd(p,k);
            p/=GCD;
            k/=GCD;
            m--;
            n--;
        }
    } else p=1;

    return p;
}