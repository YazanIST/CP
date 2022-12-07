bool LessThanOrEqual(double a,double b){return fabs(a - b) <= 1e-6 || a < b;}
struct point{
    double x,y;
    point(double a = 0,double b = 0){x = a;y = b;}
    void sc(){scanf("%lf%lf",&x,&y);}
    double ang(){return atan2(y,x);}
    double angdeg(){
        double ret = 180*atan2(y,x)/acos(-1);
        if(ret < 0)ret+=360;
        return ret;
    }
    point normal(){return point(x/len(),y/len());}
    double len(){return sqrt(y*y + x*x);}
    point operator+(const point &a){return point(x + a.x,y + a.y);}
    point operator-(const point &a){return point(x - a.x,y - a.y);}
    double operator*(const point &a){return a.x*x + a.y*y;}
    double operator^(const point &a){return x*a.y - a.x*y;}
    bool operator<(point b){if(x != b.x)return x < b.x;return y < b.y;}
    double dis(point a){return sqrt((x - a.x)*(x - a.x) + (y - a.y)*(y - a.y));}
    point mid(point a){return point((a.x + x)/2,(a.y + y)/2);}
};
struct circle{//center raduis
    point center;
    double r;
    circle(point a,double x = 0){center = a;r = x;}
    bool has(point a){return LessThanOrEqual((center - a).len(),r);}
};
struct line{//ax + by = c
    double a,b,c;
    line(double x = 0,double y = 0,double z = 0){a = x;b = y;c = z;}
    line(point x,point y){
        point temp = x - y;
        a = -temp.y;
        b = temp.x;
        c = a*x.x + b*x.y;
    }
    line operator*(double x){return line(a*x,b*x,c*x);}
    line operator/(double x){return line(a/x,b/x,c/x);}
    line perp(){
        line ret = *this;
        swap(ret.a,ret.b);
        ret.a*=-1;
        return ret;
    }
    line perp(line a,point p){return line(-a.b,a.a,-a.b*p.x + a.a*p.y);}
    point inter(line o){
        double x = o.b*c - b*o.c;
        double y = a*o.c - o.a*c;
        double z = a*o.b - o.a*b;    
        return point(x/z,y/z);
    }
};
bool InTriangle(point a,point b,point c,point d){return ((b - a)^(d - a)) <= 0 && ((c - b)^(d - b)) <= 0 && ((a - c)^(d - c)) <= 0;}//Points should be sorted in clockwise

circle CircleDefinedBypoints(point a,point b){return circle(a.mid(b),(a - a.mid(b)).len());}
circle CircleDefinedBypoints(point a,point b,point c){
    line x(a.mid(b),b),y(b.mid(c),c);
    point temp = x.perp(x,a.mid(b)).inter(y.perp(y,b.mid(c)));
    circle ret(temp,(a - temp).len());
    return ret;
}
double PointToLine(point a,point b,point c,bool seg){
    if(seg && (((c - a)*(b - a)) < 0 || ((c - b)*(a - b)) < 0))return min((c - a).len(),(c - b).len());
    return abs((c - a)^(b - a))/(b - a).len();
}
vector<point> ConvexHull(point *a,int n){
    vector<point>ret;
    int at = 0;
    for(int i = 0;i < n;i++)
        if(a[i].x < a[at].x)at = i;
        else if(a[i].x == a[at].x && a[i].y < a[at].y)at = i;
    swap(a[0],a[at]);
    sort(a + 1,a + n,[&a](point x,point y){
        x = x - a[0];
        y = y - a[0];
        long long temp = x^y;
        if(!temp)return x.len() < y.len();
        return temp < 0;
    });
    ret.push_back(a[0]);
    for(int j = 1;j < n;j++){
        while(ret.size() > 1){
            point one = ret.back() - ret[ret.size() - 2];
            point two = a[j] - ret[ret.size() - 2];
            if((one^two) < 0)break;
            ret.pop_back();
        }
        ret.push_back(a[j]);
    }
    return ret;
}
double AreaOfPolygon(point *a,int size) {
    double area = 0;
    for (int i = 0; i < size; ++i)area += a[i]^a[(i + 1)%size];
    return fabs(area)/2.0;
}
vector<point>v;
circle FindMinimumEnclosingcircle(){
    if(v.empty())return circle(point(0,0),0);
    if(v.size() == 1)return circle(v[0],0);
    if(v.size() == 2)return CircleDefinedBypoints(v[0],v[1]);
    return CircleDefinedBypoints(v[0],v[1],v[2]);
}
circle MinimumEnclosingCircle(int u){
    if(v.size() == 3 || u == n)return FindMinimumEnclosingcircle();
    circle ret = MinimumEnclosingCircle(u + 1);
    if(ret.has(a[u]))return ret;
    v.push_back(a[u]);
    ret = MinimumEnclosingCircle(u + 1);
    v.pop_back();
    return ret;
}
bool intersect(point a,point b,point c,point d){return ((a - b)^(c - b))*((a - b)^(d - b)) <= 0 && ((d - c)^(b - c))*((d - c)^(a - c)) <= 0;}
