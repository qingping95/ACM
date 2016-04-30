struct line
{
    Point P;
    Vector v;
    double ang;
    line(){}
    line(Point P, Vector v):P(P), v(v){ang = atan2(v.y, v.x);}//点和向量
    line(double a, double b, double c)//从一般式转化过来
    {
        v = Vector(b, -a);
        if(b != 0) P = Point(0, -c/b);
        else P = Point(-c/a, 0);
        Vector nor = Normal(v);
        Point tmp = nor + P;
        if(dcmp(a * tmp.x + b * tmp.y + c) > 0){//这里保证是ax+by+c <= 0的半平面
            v = v*-1;
        }
        ang = atan2(v.y, v.x);
    }
    bool operator<(const line &o)const{
        return ang < o.ang;
    }
}L[111];
bool OnLeft(line L, Point P)
{
    return Cross(L.v, P - L.P) > 0;
}
Point GetIntersection(line a, line b)
{
    Vector u = a.P - b.P;
    double t = Cross(b.v, u) / Cross(a.v, b.v);
    return a.P + a.v*t;
}
//函数过后， L的顺序会改变。返回半平面交的凸包的节点数。
LL HalfPlaneIntersection(line* L, LL n, Point* poly)
{
    sort(L, L+n);
    LL first, last;
    Point *p = new Point[n];
    line *q = new line[n];
    q[first = last = 0] = L[0];
    for(LL i = 1; i < n ;i++)
    {
        while(first < last && !OnLeft(L[i], p[last - 1])) last--;
        while(first < last && !OnLeft(L[i], p[first])) first++;
        q[++last] = L[i];
        if(fabs(Cross(q[last].v, q[last-1].v)) < eps){
            last--;
            if(OnLeft(q[last], L[i].P)) q[last] = L[i];
        }
        if(first < last) p[last - 1] = GetIntersection(q[last - 1], q[last]);
    }
    while(first < last && !OnLeft(q[first], p[last - 1])) last -- ;
    if(last - first <= 1) return 0;
    p[last] = GetIntersection(q[last], q[first]);
    LL m = 0;
    for(LL i = first; i <= last; i++) poly[m++] = p[i];
    return m;
}