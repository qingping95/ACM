/*
*Rainto96
*Beijing University of Posts and Telecommunications School of Software Engineering
*http://blog.csdn.net/u011775691
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define VINT vector<int>
#define PII pair<int,int>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned ll
#define MEM0(x)  memset(x,0,sizeof(x))
#define MEM(x,val) memset((x),val,sizeof(x))
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
#define LD long double
using namespace std;
struct Point3{
        LD x,y,z;
        Point3(LD x=0, LD y=0, LD z=0):x(x),y(y),z(z){}
        void read(){
                //scanf("%lf%lf%lf",&x,&y,&z);
                cin>>x>>y>>z;
        }
        LD len(){
                return sqrt(x*x + y*y + z*z);
        }
};
typedef Point3 Vector3;
const LD eps = 1e-10;
int dcmp(LD x){
        return x<-eps? -1 : x>eps;
}
Vector3 operator + (Vector3 A, Vector3 B){return Vector3(A.x + B.x, A.y + B.y, A.z + B.z);}
Vector3 operator - (Vector3 A, Vector3 B){return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);}
Vector3 operator * (Vector3 A, LD p){return Vector3(A.x * p, A.y * p, A.z * p);}
Vector3 operator / (Vector3 A, LD p){return Vector3(A.x / p, A.y / p, A.z / p);}
struct Line3{
        Point3 p;
        Vector3 v;
        Line3(Point3 p = Point3(0,0), Vector3 v = Point3(0,0)):p(p),v(v){}
        Point3 point(LD t){
                return p+v*t;
        }
};
LD Dot(Vector3 A, Vector3 B){
        return A.x * B.x + A.y * B.y + A.z * B.z;
}
Vector3 Cross(Vector3 A, Vector3 B){
        return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z , A.x * B.y - A.y * B.x);
}
bool LineDistance3D1(Point3 p1, Vector3 u, Point3 p2, Vector3 v, LD& s){
        LD b = Dot(u,u) * Dot(v,v) - Dot(u,v) * Dot(u,v);

        if(dcmp(b) == 0) {
                for(;;);
                return false;
        }
        LD a = -Dot(u,v) * Dot(v, p2-p1) + Dot(v,v) * Dot(u,p2-p1);
        s = a/b;
        return true;
}

LD line2line(Line3 u, Line3 v){
        Point3 n = Cross(u.v*(-1.0), v.v*(-1.0));
        return abs(Dot(u.p - v.p, n)) / n.len();
}
#define D(x) (x)*(x)
LD p2p(Point3 p1 ,Point3 p2){
        return sqrt(D(p1.x - p2.x) + D(p1.y - p2.y) + D(p1.z - p2.z) );
}
int main(){
	#ifndef ONLINE_JUDGE
                //freopen("C:/OJ/in.txt","r",stdin);
	#endif
	cin.sync_with_stdio(false);
	int T;cin>>T;
	while(T--){
                Point3 p[4];
                for(int i=0;i<4;i++)
                        p[i].read();
                Line3 l1 = Line3(p[0],p[1] - p[0]);
                Line3 l2 = Line3(p[2],p[3] - p[2]);
                LD s,t;
                LineDistance3D1(l1.p, l1.v, l2.p, l2.v, s);
                Point3 p1 = l1.point(s);
                LineDistance3D1(l2.p, l2.v, l1.p, l1.v, t);
                Point3 p2 = l2.point(t);
                LD dis1 = line2line(l1,l2);
                //LD dis2 = p2p(p1,p2);
                //printf("%.6Lf\n",dis1);
                //printf("%.6Lf %.6Lf %.6Lf ",p1.x,p1.y,p1.z);
                //printf("%.6Lf %.6Lf %.6Lf\n",p2.x,p2.y,p2.z);
                cout<<fixed<<dis1<<endl;
                cout<<p1.x<<" "<<p1.y<<" "<<p1.z<<" "<<p2.x<<" "<<p2.y<<" "<<p2.z<<endl;
	}
        return 0;
}
