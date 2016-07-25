///*
//*Rainto96
//*Beijing University of Posts and Telecommunications School of Software
//Engineering
//*http://blog.csdn.net/u011775691
//*/
//#include <iostream>
//#include <cstdio>
//#include <algorithm>
//#include <queue>
//#include <cstring>
//#include <string>
//#include <cmath>
//#include <set>
//#include <map>
//#include <vector>
//#include <climits>
//#include <bitset>
//using namespace std;
//#define pb push_back
//#define ALL(x) x.begin(),x.end()
//#define VINT vector<int>
//#define PII pair<int,int>
//#define MP(x,y) make_pair((x),(y))
//#define ll long long
//#define ull unsigned ll
//#define MEM0(x)  memset(x,0,sizeof(x))
//#define MEM(x,val) memset((x),val,sizeof(x))
//#define scan(x) scanf("%d",&(x))
//#define scan2(x,y) scanf("%d%d",&(x),&(y))
//#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
//#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
//#define Max(a,b) a=max(a,b)
//#define Min(a,b) a=min(a,b)
//#define fuck(x) cout<<#x<<" "<<x<<endl
//const double eps = 1e-10;
//const double pi = acos(-1.0);
//inline int cmp(double a)
//{
//    return a < -eps ? -1 : a > eps;
//}
//inline double Sqr(double a)
//{
//    return a*a;
//}
//inline double Sqrt(double a)
//{
//    return a <= 0 ? 0 : sqrt(a);
//}
//struct Point{
//    double x, y, z;
//    Point(double x = 0, double y = 0, double z = 0):x(x), y(y), z(z){
//    }
//    void read()
//    {
//        scanf("%lf%lf%lf", &x, &y, &z);
//    }
//    void print()
//    {
//        printf("%.10f %.10f %.10f\n", x, y, z);
//    }
//    double Length()const {
//        return Sqrt(Sqr(x)+Sqr(y)+Sqr(z));
//    }
//};
//Point operator+(Point a, Point b){
//    return Point(a.x+b.x, a.y+b.y, a.z+b.z);
//}
//Point operator-(Point a, Point b){
//    return Point(a.x-b.x, a.y-b.y, a.z-b.z);
//}
//Point operator*(Point a, double b){
//    return Point(a.x*b, a.y*b, a.z*b);
//}
//Point operator/( Point a, double b){
//    return Point(a.x/b, a.y/b, a.z/b);
//}
//bool operator==( Point a, Point b){
//    return cmp(a.x-b.x) == 0 && cmp(a.y-b.y) == 0 && cmp(a.z-b.z) == 0;
//}
//bool operator!=( Point a, Point b){
//    return !(a == b);
//}
//Point Unit(Point A){
//    return A/A.Length();
//}
//double Dot(const Point a, const Point b){
//    return a.x*b.x+a.y*b.y+a.z*b.z;
//}
//Point Det(const Point a, Point b){
//    return Point(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
//}
//struct Line{
//    Point a, b;
//    Line(Point a, Point b):a(a), b(b){}
//};
//double vlen(Point P){
//    return P.Length();
//}
//bool zero(double x) {return fabs(x) < eps;}
//double angle_cos(Line u, Line v){
//    return Dot(u.a-u.b, v.a-v.b)/vlen(u.a-u.b)/vlen(v.a-v.b);
//}
//int parallel(Line u, Line v){
//    return vlen(Det(u.a-u.b, v.a-v.b))<eps;
//}
//Point pvec(Point s1, Point s2, Point s3){
//    return Det((s1-s2), (s2-s3));
//}
//int dots_onplane(Point a, Point b, Point c, Point d){
//    return zero(Dot(pvec(a,b,c), d-a));
//}
//Point intersection(Line u, Line v)
//{
//    Point ret = u.a;
//    if(cmp((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x)) == 0) return ret;
//    double t = ((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
//            /((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
//    ret = ret + (u.b-u.a)*t;
//    return ret;
//}
//int dots_inline(Point a, Point b, Point c)
//{
//    return vlen(Det(a-b, b-c))<eps;
//}
//Point rotate(Point a, Point b, double ang)
//{
//    Point e1, e2, e3;
//    e3 = Unit(b);
//    double len = Dot(a, e3);
//    Point p = e3*len;
//    e1 = a-p;
//    if(e1.Length() > eps) Unit(e1);
//    e2 = Det(e1, e3);
//    double x1 = Dot(a, e1), y1 = Dot(a, e2);
//    double x = x1*cos(ang) - y1*sin(ang);
//    double y = x1*sin(ang) + y1*cos(ang);
//    return e1*y + e2*x + p;
//}
//int main(){
//    //freopen("/home/rainto96/in.txt","r",stdin);
//    Point A, B, C, D;
//    A.read();
//    B.read();
//    C.read();
//    D.read();
//    if(dots_inline(A, B, C) && dots_inline(A, B, D)){
//        Point(1, 1, 1).print();
//        Point(2, 3, 5).print();
//        printf("360\n");
//    }else if(dots_onplane(A, B, C, D)){
//        if(parallel(Line(A, B), Line(C, D))){
//            Point E = (A+C)/2;
//            Point F = (A+D)/2;
//            E.print();
//            if(cmp(vlen(E-F)-1) < 0) F = E+Unit(F-E)*2;
//            F.print();
//            printf("180\n");
//        }else{
//            Point v;
//            if(A != D && B != D) v = pvec(A, B, D);
//            else v = pvec(A, B, C);
//            v = Unit(v)*2;
//            Point E = intersection(Line(A, B), Line(C, D));
//            E.print();
//            (E+v).print();
//            double ang = acos(angle_cos(Line(C, D), Line(A, B)));
//            ang = ang*180.0/pi;
//            if(ang < 0)  ang += 360;
//            printf("%.10f\n", ang);
//        }
//    }else{
//        printf("Impossible\n");
//    }
//    return 0;
//}
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#define clr(a) memset(a, 0, sizeof(a))

typedef std::pair<int, int> pii;
typedef long long ll;

	#define LL "%lld"

const double eps = 1e-9;

void dbg(const char * fmt, ...)
{
	#ifndef ONLINE_JUDGE
		va_list args;
		va_start(args, fmt);
		vfprintf(stdout, fmt, args);
		va_end(args);
		fflush(stdout);
	#endif
}

class point
{
public:
	double x,y,z;
	void read()
	{
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	void print() const
	{
		printf("%.10f %.10f %.10f\n", x, y, z);
	}
	point() : x(0), y(0), z(0)
	{}
	point(double x, double y, double z) : x(x), y(y), z(z)
	{}
	point operator + (const point &p) const
	{
		return point (x + p.x, y + p.y, z + p.z);
	}
	point operator - (const point &p) const
	{
		return point (x - p.x, y - p.y, z - p.z);
	}
	point operator * (const point &p) const
	{
		return point (y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
	}
	point operator * (double a) const
	{
		return point (x * a, y * a, z * a);
	}
	point operator / (double a) const
	{
		return point (x / a, y / a, z / a);
	}
	double operator % (const point &p) const
	{
		return x * p.x + y * p.y + z * p.z;
	}
	double len2()
	{
		return (*this) % (*this);
	}
	double len()
	{
		return sqrt(len2());
	}
};
double Dot(const point a, const point b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}
point Det(const point a, point b){
    return point(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
point pvec(point s1, point s2, point s3){
    return Det((s1-s2), (s2-s3));
}
bool zero(double x) {return fabs(x) < eps;}
int dots_onplane(point a, point b, point c, point d){
    return zero(Dot(pvec(a,b,c), d-a));
}
int main()
{
	point a, va, b, vb;
	a.read(); va.read();
	va = va - a;
	b.read(); vb.read();
	vb = vb - b;
	//if(!dots_onplane(a, va, b, vb)){
		//printf("Impossible\n");
	//}else{
		double a1 = va % va;
		double b1 = -(va % vb);
		double c1 = (a-b) % va;
		double a2 = va % vb;
		double b2 = - (vb % vb);
		double c2 = (a-b) % vb;
		double d = a2 * b1 - a1 * b2;

		double x, y;
		if (fabs(d) < eps)
		{
			x = y = 0;
		}
		else
		{
			x = (c1 * b2 - c2 * b1) / d;
			y = (c2 * a1 - c1 * a2) / d;
		}

		point p = a + va * x;
		point q = b + vb * y;

		point m = (p+q) / 2;
		point vm = (va / va.len()) + (vb / vb.len());

		m.print();
		(m+vm).print();
		printf("%.10f\n", 180.);
	//}
	return 0;
}
