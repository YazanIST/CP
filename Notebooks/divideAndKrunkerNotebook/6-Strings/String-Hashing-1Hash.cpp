void calcPowers(){
    powers.push_back(1);
    for (int i = 0; i < N; i++) {
        powers.push_back(mul(powers.back(), PRIME));
    }
    for (auto x:powers){
        powersInv.push_back(inv(x));
    }
}

vector<int> calcHash(const string &s) {
    vector<int>ret(s.size());
    for (int i = 0; i < (int) s.size(); i++) {
        if (i) {
            ret[i] = ret[i-1];
        }
        ret[i] = add(ret[i-1], mul(s[i], powers[i]));
    }
    return ret;
}

int getHash(const vector<int> &hash, int l, int r){
    if (l == 0) {
        return hash[r];
    }
    return mul(sub(hash[r], hash[l-1]), powersInv[l]);
}