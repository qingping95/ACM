struct Point
{
    double x,y;
    Point(double x = 0, double y = 0):x(x),y(y){}
	void read()
    {
        scanf("%lf%lf", &x, &y);
    }
}pa[N],pb[N];
const double eps = 1e-10;
const double PI = acos(-1.0);
typedef Point Vector;
int dcmp(double x){if(fabs(x) < eps) return 0;else return x<0?-1:1;}
int dcmp(double x)
{
    return (x>eps)-(x<-eps);
}
Vector operator+(Vector A,Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator-(Point A,Point B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator*(Vector A, double p){return Vector(A.x*p, A.y*p);}
Vector operator/(Vector A, double p){return Vector(A.x/p, A.y/p);}
bool operator<(const Point& a, const Point& b){return a.x<b.x || (a.x == b.x && a.y < b.y);}
bool operator==(const Point& a, const Point& b){return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;}
//返回值(-PI, PI]
double angle(Vector A){return atan2(A.y,A.x);}//返回A向量的极角atan2(y,x)所表达的意思是坐标原点为起点，指向(x,y)的射线在坐标平面上与x轴正方向之间的角的角度。

double Dot(Vector A, Vector B){return A.x*B.x+A.y*B.y;}
double Length(Vector A){return sqrt(Dot(A,A));}
double Angle(Vector A,Vector B){return acos(Dot(A,B)/Length(A)/Length(B));}//A到B的逆时针转的角
double Cross(Vector A, Vector B){return A.x*B.y-A.y*B.x;}
Vector Rotata(Vector A,double rad){return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));}//A逆时针转ang弧度
double torad(double ang){return ang / 180 * PI;}
Vector Normal(Vector A){double L = Length(A); return Vector(-A.y/L, A.x/L);}//需要确保A不是0向量，左转90度
//非规范相交，端点上视为在线段上
bool OnSegment(Point p, Point a, Point b) { return dcmp(Length(p - a) + Length(p - b) - Length(a - b)) == 0; }//精度也很高的！
double NormalAng(double x)//将弧度x通过+-2*PI的方式约束到[-PI,PI];
{
    if(x > 0){
        while(x > PI) x -= 2.0 * PI;
    }else{
        while(x < -PI) x += 2.0 * PI;
    }
    return x;
}
struct Line{
    Point p,v;
    double a,b,c;//得到一般式的参数
	double ang;
	Line(){}
    Line(Point p = Point(0,0), Vector v = Vector(0,0)):p(p),v(v){a = v.y - p.y; b = p.x - v.x; c = p.y*v.x - v.y*p.x;ang = angle(v);}
    Point point(double t){return p + v*t;}//只能在点斜式中用
    bool operator < (const Line& L)const{
        return ang < L.ang;
    }
}L[N];
struct Circle
{
    Point c;
    double r;
    Circle(){}
    Circle(Point c, double r):c(c),r(r){}
    Point point(double a)
    {
        return Point(c.x + cos(a)*r, c.y+sin(a)*r);
    }
};
bool OnSegment(Point p, Point a1, Point a2){return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;}
bool OnSegment(Point p, Point a, Point b)//精度较高的判断
{
    Point v1,v2;
    v1=p-a;
    v2=p-b;

    if( dcmp(Cross(v1,v2))!=0)  //叉积不为0 就不在直线上
        return 0;
    else
    {
        if(dcmp(min(a.x,b.x)- p.x)<=0 && dcmp(p.x-max(a.x,b.x))<=0 && dcmp(min(a.y,b.y)- p.y)<=0 && dcmp( p.y-max(a.y,b.y))<=0)
            return 1;
        else
            return 0;
    }
}
//根据一个极角，返回相应极角的向量
Vector getVFromAngle(double ang)
{
    Vector V;
    if(dcmp(ang - PI/2) == 0) V = Vector(1, 1);
    else if(dcmp(ang + PI/2) == 0) V = Vector(1, -1);
    else{
        V = Vector(1, tan(ang));
    }
    return V;
}
//两直线相交
Point GetLineIntersection(Point P,Vector v, Point Q, Vector w)
{
    Vector u = P-Q;
    double t = Cross(w,u)/ Cross(v,w);
    return P+v*t;
}
//点到线段距离
double DistanceToSegment(Point P, Point A, Point B)
{
    if(A==B) return Length(P-A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1, v3)) > 0) return Length(Length(v3));
    else return fabs(Cross(v1, v2)) / Length(v1);
}
//点到直线距离
double DistanceToLine(Point P, Point A, Point B)
{
    Vector v1 = B-A,v2 = P-A;
    return fabs(Cross(v1,v2)) / Length(v1);
}
//线段是否规范相交
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1);
    double c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
//过点P的圆C的切线
int getTangents(Point P, Circle C, Vector* v)
{
    Vector u = C.c - P;
    double dist = Length(u);
    if(dist < C.r) return 0;
    if(dcmp(dist - C.r) == 0) {
        v[0] = Rotata(u, PI/2);
        return 1;
    }
    double ang = asin(C.r/dist);
    v[0] = Rotata(u, -ang);
    v[1] = Rotata(u, ang);
    return 2;
}
//圆圆相交
int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol)
{
    double d = Length(C1.c-C2.c);
    if(dcmp(d) == 0)
    {
        if(dcmp(C1.r-C2.r) == 0) return -1;
        return 0;
    }
    if(dcmp(C1.r + C2.r - d ) < 0) return 0;
    if(dcmp(fabs(C1.r-C2.r) - d) > 0) return 0;

    double a = angle(C2.c-C1.c);
    double da = acos((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d));
    Point P1 = C1.point(a - da), P2 = C1.point(a + da);
    sol.push_back(P1);
    if(P1 == P2) return 1;
    sol.push_back(P2);
    return 2;
}
//直线与圆相交,直线必须是点斜式,如果是线段的话，需要检查t1,t2是否在[0,1]之间。
int getLineCircleIntersection(Line L, Circle C, vector<Point >& sol)
{
    double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
    double e = a*a + c*c, f = 2*(a * b + c * d), g = b*b+d*d-C.r*C.r;
    double delta = f*f - 4*e*g;
    double dist = DistanceToLine(C.c, L.p, L.p + L.v);
    double t1,t2;
    if(dcmp(dist - C.r) > 0) return 0;
    if(dcmp(dist - C.r) == 0) {
        t1 = t2 = -f / (2*e); sol.push_back(L.point(t1));
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (2*e); sol.push_back(L.point(t1));
    t2 = (-f + sqrt(delta)) / (2*e); sol.push_back(L.point(t2));
    return 2;
}
//计算多边形的有向面积
double PolygonArea(Point* p, int n)
{
    double area = 0;
    for(int i=1;i<n-1;i++) area += Cross(p[i]-p[0], p[i+1]-p[0]);
    return area/2;
}
//判断点是否在多边形（可以是凹多边形）的内部
int isPointInPolygon(Point p, Point* poly, int n)
{
    int wn = 0;
    for(int i = 0; i<n; i++)
    {
        if(OnSegment(p, poly[i], poly[(i+1)%n])) return -1;//边界
        int k = dcmp(Cross(poly[(i+1)%n]-poly[i], p-poly[i]));
        int d1 = dcmp(poly[i].y - p.y);
        int d2 = dcmp(poly[(i+1)%n].y - p.y);
        if(k>0 && d1 <= 0 && d2 > 0) wn++;
        if(k<0 && d2 <= 0 && d1 > 0) wn--;
    }
    if(wn != 0) return 1;//内部
    return 0;//外部
}
//点是否在凸多边形内
bool isPointInConvexPolygon(Point p, Point* poly, int n)
{
    for(int i=0;i<n;i++)
        if(dcmp(Cross(poly[(i+1)%n] - poly[i], p - poly[i])) <= 0) return 0;
    return 1;
}


//两圆交面积
const long double eps = 1e-13;
const long double PI = acos(-1.0);
int dcmp(long double x)
{
    return (x > 0) - (x < 0);
}
long double solve(Point c1, long double r1, Point c2, long double r2)
{
    long double a = dist(c1, c2), b = r1, c = r2;
    if(dcmp(a - r1 - r2) >= 0) return 0;
    if(dcmp(a + r1 - r2) <= 0) return r1*r1*PI;
    if(dcmp(a + r2 - r1) <= 0) return r2*r2*PI;

    long double cta1 = acos((a*a+b*b-c*c)/2/(a*b));
    long double cta2 = acos((a*a+c*c-b*b)/2/(a*c));
    long double s1 = r1*r1*cta1 - r1*r1*sin(cta1)*(a*a+b*b-c*c)/2/(a*b);
    long double s2 = r2*r2*cta2 - r2*r2*sin(cta2)*(a*a+c*c-b*b)/2/(a*c);
    return s1 + s2;
}
