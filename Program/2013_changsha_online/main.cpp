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
using namespace std;
const double eps = 1e-10;
double dmod2(double x)
{
    int res = x/2.0 + eps;
    if(abs(res * 2 - x)<eps ) return 0;
    else
    {
        int tmp = res;
        return x - tmp*2;
    }
}
struct PIII
{
    double x,y,z;
    PIII(double x=0,double y=0, double z=0):x(x),y(y),z(z) {}
};
int dcmp(double x)
{
    return x < -eps ? -1 : x > eps;
}
PIII hsv2rgb(double H,double S,double V)
{
    double C = V*S;
    double Hp = H/60.0;
    double X = C*(1-abs(dmod2(Hp) - 1));
    double m = V - C;
    PIII res;
    if(Hp>=0 && Hp<1) res = PIII(C,X,0);
    else if(dcmp(Hp-1)>=0 && dcmp(Hp-2)<0) res = PIII(X,C,0);
    else if(dcmp(Hp-2)>=0 && dcmp(Hp-3)<0) res = PIII(0,C,X);
    else if(dcmp(Hp-3)>=0 && dcmp(Hp-4)<0) res = PIII(0,X,C);
    else if(dcmp(Hp-4)>=0 && dcmp(Hp-5)<0) res = PIII(X,0,C);
    else if(dcmp(Hp-5)>=0 && dcmp(Hp-6)<0) res = PIII(C,0,X);
    else res = PIII(0,0,0);
    res = PIII(res.x+m , res.y + m, res.z + m);
    return res;
}
PIII hsl2rgb(double H,double S,double L)
{
    double C = (1-abs(2*L - 1)) * S;
    double Hp = H/60.0;
    double X = C*(1-abs(dmod2(Hp) - 1));
    double m = L - C*0.5;
    PIII res;
    if(Hp>=0 && Hp<1) res = PIII(C,X,0);
    else if(dcmp(Hp-1)>=0 && dcmp(Hp-2)<0) res = PIII(X,C,0);
    else if(dcmp(Hp-2)>=0 && dcmp(Hp-3)<0) res = PIII(0,C,X);
    else if(dcmp(Hp-3)>=0 && dcmp(Hp-4)<0) res = PIII(0,X,C);
    else if(dcmp(Hp-4)>=0 && dcmp(Hp-5)<0) res = PIII(X,0,C);
    else if(dcmp(Hp-5)>=0 && dcmp(Hp-6)<0) res = PIII(C,0,X);
    else res = PIII(0,0,0);
    res = PIII(res.x+m , res.y + m, res.z + m);
    return res;
}
PIII rgb2hsl(double R,double G,double B)
{
    //R = R/255; G = G/255; B = B/255;
    double maxn = max(R,max(G,B));
    double minn = min(R,min(G,B));
    double h,s;
    if(abs(maxn - minn) < eps) h = 0;
    else if(dcmp(maxn - R)==0 && dcmp(G-B)>=0) h = 60*(G-B)/(maxn - minn);
    else if(dcmp(maxn - R)==0 && dcmp(G-B)<0) h = 60*(G-B)/(maxn - minn) + 360;
    else if(dcmp(maxn - G)==0) h = 60*(B-R)/(maxn - minn) + 120;
    else if(dcmp(maxn - B)==0) h = 60*(R-G)/(maxn - minn) + 240;
    while(dcmp(h-360)>=0) h-=360;

    double l = (maxn + minn) * 0.5;
    if(abs(l)<eps || dcmp(maxn - minn)==0 ) s=0;
    else if(l>eps && dcmp(l-0.5)<=0) s = (maxn - minn) / (maxn + minn);
    else s=(maxn - minn) / (2.0-(maxn + minn));
    return PIII(h,s,l);
}
PIII rgb2hsv(double R,double G,double B)
{
    //R = R/255; G = G/255; B = B/255;
    double maxn = max(R,max(G,B));
    double minn = min(R,min(G,B));
    double h;
    if(abs(maxn - minn) < eps) h = 0;
    else if(dcmp(maxn - R)==0 && dcmp(G-B)>=0) h = 60*(G-B)/(maxn - minn);
    else if(dcmp(maxn - R)==0 && dcmp(G-B)<0) h = 60*(G-B)/(maxn - minn) + 360;
    else if(dcmp(maxn - G)==0) h = 60*(B-R)/(maxn - minn) + 120;
    else if(dcmp(maxn - B)==0) h = 60*(R-G)/(maxn - minn) + 240;
    while(dcmp(h-360)>=0) h-=360;
    double s,v;
    if(abs(maxn) < eps) s=0;
    else s = (maxn - minn) / maxn;

    v = maxn;
    return PIII(h,s,v);
}
double get(char str[])
{
    char que[33];
    int tail=0;
    int len = strlen(str);
    for(int i=0; i<len; i++)
        if(str[i]!='%') que[tail++] = str[i];
        else break;
    int sum =0;
    for(int i=0; i<tail; i++)
    {
        sum = sum*10 + (que[i] - '0');
    }
    return sum*1.0/100;
}
void print(char str[],double x,double y,double z)
{
    printf("%s %.0f %.0f%% %.0f%%\n",str,x+eps,y+eps, z+eps);
    int res = x+eps;
    if(res == 360) while(1);
//    putchar('%');
//    printf(" %.0f",z);
//    putchar('%');
//    putchar('\n');
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("F:/in.txt","r",stdin);
#endif
    char to[66] , from[66];
    while(scanf("%s",to) == 1)
    {
        scanf("%s",from);
        if(strcmp(from,"RGB")==0)
        {
            double R,G,B;
            scanf("%lf%lf%lf",&R,&G,&B);
            if(strcmp(to,"HSL")==0)
            {
                PIII res = rgb2hsl(R/255.0,G/255.0,B/255.0);
                //print(to,rd(res.x),rd(res.y*100),rd(res.z*100));
                print(to,(res.x),(res.y*100),(res.z*100));
            }
            else if(strcmp(to,"HSV")==0)
            {
                PIII res = rgb2hsv(R/255.0,G/255.0,B/255.0);
                //print(to,rd(res.x),rd(res.y*100),rd(res.z*100));
                print(to,(res.x),(res.y*100),(res.z*100));
            }else{
                PIII res = PIII(R, G, B);
                printf("%s %.0f %.0f %.0f\n",to,(res.x+eps),(res.y+eps),(res.z+eps));
            }
        }
        else if(strcmp(from,"HSV")==0)
        {
            double H,S,V;
            char s1[66],s2[66];
            scanf("%lf",&H);
            scanf("%s%s",s1,s2);
            S=get(s1) , V=get(s2);
            //cerr<<H<<" "<<S<<" "<<V<<endl;
            if(strcmp(to,"RGB")==0)
            {
                PIII res = hsv2rgb(H,S,V);
                //printf("%s %d %d %d\n",to,rd(res.x*255),rd(res.y*255),rd(res.z*255));
                printf("%s %.0f %.0f %.0f\n",to,(res.x*255+eps),(res.y*255+eps),(res.z*255+eps));
            }
            else if(strcmp(to,"HSL")==0)
            {
                PIII res = hsv2rgb(H,S,V);
                res = rgb2hsl(res.x,res.y,res.z);
                //print(to,rd(res.x),rd(res.y*100),rd(res.z*100));
                print(to,(res.x),(res.y*100),(res.z*100));
            }else{
                print(to, H, S*100, V*100);
            }
        }
        else if(strcmp(from,"HSL")==0)
        {
            double H,S,L;
            char s1[66],s2[66];
            scanf("%lf",&H);
            scanf("%s%s",s1,s2);
            S=get(s1) , L=get(s2);
            if(strcmp(to,"RGB")==0)
            {
                PIII res = hsl2rgb(H,S,L);
                //printf("%s %d %d %d\n",to,rd(res.x*255),rd(res.y*255),rd(res.z*255));
                printf("%s %.0f %.0f %.0f\n",to,(res.x*255+eps),(res.y*255+eps),(res.z*255+eps));
            }
            else if(strcmp(to,"HSV")==0)
            {
                PIII res = hsl2rgb(H,S,L);
                res = rgb2hsv(res.x,res.y,res.z);
                //print(to,rd(res.x),rd(res.y*100),rd(res.z*100));
                print(to,(res.x),(res.y*100),(res.z*100));
            }else{
                print(to, H, S*100, L*100);
            }
        }

    }
    return 0;
}
