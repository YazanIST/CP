int mod(string num, int a){
    int ret=0;
 
    for(int i=0;i<num.length();i++)
        ret=(ret*10+(int)num[i]-'0')%a;
 
    return ret;
}