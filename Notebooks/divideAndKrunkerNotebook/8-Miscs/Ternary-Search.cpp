const double EPS =  1e-9;

int n;
int f(int x) { }

ll TS_integers() {
    int l = 0, r = n - 1;
    ll cur = INT32_MAX;
    while(l <= r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
 
        ll f1 = f(m1);
        ll f2 = f(m2);
        cur = min(f1, f2);
 
        (f1 >= f2) ? l = m1 + 1 : r = m2 - 1;  
    }
    
    return cur;
}

double TS_double() {
    double l = 0;
    double r = 1000;
    while(r - l > EPS) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        
        double val1 = f(m1);
        double val2 = f(m2);
 
        (val1 > val2) ? l = m1 : r = m2; 
    }
    
    return f(l);
}