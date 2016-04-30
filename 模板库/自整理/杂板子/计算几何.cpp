
//计算几何
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <cstdlib>
#include <queue>
#include <stack>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <set>
#define PI acos(-1.0)
#define maxn 100005
#define INF 0x7fffffff
#define eps 1e-8
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
int cmp(double x)
{
  if(fabs(x)<eps)
    return 0;
  if(x>0)
    return 1;
  return -1;
}
inline int sgn(double n)
{
  return fabs(n)<eps?0:(n<0?-1:1);
}
inline double sqr(double x)
{
  return x*x;
}
struct point//点
{
  double x,y;
  point() {}
  point(double a,double b):x(a),y(b) {}
  void input()
  {
    scanf("%lf%lf",&x,&y);
  }
  friend point operator + (const point &a,const point &b)
  {
    return point(a.x+b.x,a.y+b.y);
  }
  friend point operator - (const point &a,const point &b)
  {
    return point(a.x-b.x,a.y-b.y);
  }
  friend bool operator == (const point &a,const point &b)
  {
    return cmp(a.x-b.x)==0 &&cmp(a.y-b.y)==0;
  }
  friend point operator * (const point &a,const double &b)
  {
    return point(a.x*b,a.y*b);
  }
  friend point operator * (const double &a,const point &b)
  {
    return point(a*b.x,a*b.y);
  }
  friend point operator / (const point &a,const double &b)
  {
    return point(a.x/b,a.y/b);
  }
  double norm()
  {
    return sqrt(sqr(x)+sqr(y));
  }//到原点距离
  void out () const
  {
    printf("%.2f %.2f",x,y);
  }
};
double det (const point &a,const point &b)
{
  return a.x*b.y-a.y*b.x;
}//叉积
double dot (const point &a,const point &b)
{
  return a.x*b.x+a.y*b.y;
}//点乘
double dist (const point &a,const point &b)
{
  return (a-b).norm();
}//距离
point rotate_point(const point &p,double A)
{
  double tx=p.x,ty=p.y;
  return point (tx*cos(A)-ty*sin(A),tx*sin(A)+ty*cos(A));
}//旋转，A是弧度
struct line
{
  point a,b;
  line() {}
  line(point x,point y):a(x),b(y) {}
  point dire()const
  {
    return b-a;
  }//向量
  double len()
  {
    return dire().norm();
  }
};
bool parallel(line a,line b)
{
  return !cmp(det(a.a-a.b,b.a-b.b));
}
bool line_make_point (line a,line b,point &res)
{
  if(parallel(a,b))
    return false;
  double s1=det(a.a-b.a,b.b-b.a);
  double s2=det(a.b-b.a,b.b-b.a);
  res=(s1*a.b-s2*a.a)/(s1-s2);
  return true;
}
//计算几何


