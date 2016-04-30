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
#include <ctime>
using namespace std;
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define VINT vector<int>
#define PII pair<int,int>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned long long
#define MEM0(x)  memset(x,0,sizeof(x))
#define MEM(x,val) memset((x),val,sizeof(x))
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
#define fuck(x) cout<<#x<<" - "<<x<<endl
struct Date{
    int y,m,d;
    Date add(int xmonth){
        Date ans=*this;
        ans.m+=xmonth;
        if(ans.m>12){
            ans.y+=(ans.m-1)/12;
            while(ans.m>12) ans.m-=12;
        }
        ans.jiuzheng();
        return ans;
    }
    void jiuzheng(){
        if(d == 31 && m!=1 && m!=3 && m!=5 && m!=7 && m!=8 && m!=10 && m!=12){
            m++,d=1;
        }
        if(d>=30 && m==2){
            d=1;m=3;
        }
        if(d==29 && m==2){
            if((y%100==0 && y%400==0) || (y%100!=0 && y%4==0)){}
            else m=3,d=1;
        }
    }
    bool dengyu(Date s){
//        jiuzheng();
//        s.jiuzheng();
        return y==s.y && m==s.m;
    }
    bool xiaoyu(Date s){
//        jiuzheng();
//        s.jiuzheng();
        if(y<s.y) return true;
        else if(y==s.y && m < s.m) return true;
//        else if(y==s.y && m == s.m && d < s.d) return true;
        return false;
    }

};
int main()
{
    //freopen("in.txt","r",stdin);
    int M,N,K;
    scan3(M,N,K);
    Date birth;
    scanf("%2d.%2d.%d",&birth.d, &birth.m, &birth.y);
    Date st = (Date){1952,1,1};
    Date ed = (Date){2012,1,1};
    if(birth.y < 1952){
        birth.y += 60;
        birth.jiuzheng();
        printf("%02d.%02d.%d\n",birth.d, birth.m, birth.y);
    }else{
        birth.y += 60;
        Date cur = birth;
        cur.jiuzheng();
        for(int i = 0; i < K; i++)
        {
            if(ed.xiaoyu(cur) || ed.dengyu(cur)){
                ed = ed.add(N);
                cur = birth.add((i+1)*M);
            }else break;
        }
        cur.jiuzheng();
        printf("%02d.%02d.%d\n",cur.d, cur.m, cur.y);
    }
    return 0;
}
