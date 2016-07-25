#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 2000010;
int n, m;
struct node{
    int s, t;
    int lid, rid;
    node(int s = 0, int t = 0, int lid = 0, int rid = 0):s(s), t(t), lid(lid), rid(rid){}
    int getpos() const
    {
        if(s == 1) return 1;
        else if(t == n) return n;
        else return (s+t)>>1;
    }
    int getd()const {
        if(s == 1) return t;
        else if(t == n) return n - (s-1);
        else return ((s+t)>>1) - (s-1);
    }
    bool operator<(const node& o)const{
        int d = getd(),od = o.getd();
        if(d == od) return getpos() < o.getpos();
        return d > od;
    }
}lr[N][2];
set<node> S;
set<node>::iterator it, it1, it2;
int slist[N], pos[N];
void printSet(set<node> S)
{
    cout<<endl;
    for(it1 = S.begin(); it1 != S.end(); it1++)
    {
        cout<<it1->s<<" , "<<it1->t<<" , "<<it1->lid<<" , "<<it1->rid<<endl;
    }
    cout<<endl;
}
int main()
{
//    Open();

    scanf("%d%d", &n, &m);
    S.emplace(1, n, 0, 0);
//    for(int i = 0; i < N; i++)
//        lr[i][0] = lr[i][1] = S.end();
    while(m--)
    {
        int op, id;
        scanf("%d%d", &op, &id);
        if(op == 1){
            it = S.begin();
//            cout<<"find: "<<it->s<<" , "<<it->t<<" , "<<it->lid<<" , "<<it->rid<<endl;
            pos[id] = it->getpos();
            slist[pos[id]] = id;
            printf("%d\n", pos[id]);
            int res = pos[id];
            int s = it->s, t = it->t, lid = it->lid, rid = it->rid;
            lr[id][0] = lr[id][1] = node();
            if(s <= res-1){
                it1 = S.emplace(s, res-1, lid, id).first;
                lr[id][0] = (*it1);
                lr[lid][1] = (*it1);
            }else{
                lr[id][0] = lr[lid][1] = node();
            }
            if(res+1 <= t){
                it2 = S.emplace(res+1, t, id, rid).first;
                lr[rid][0] = (*it2);
                lr[id][1] = (*it2);
            }else{
                lr[rid][0] = lr[id][1] = node();
            }
            S.erase(it);
//            printSet(S);
        }else{
            if(pos[id] == 0)
                continue;
            node in1 = lr[id][0];
            node in2 = lr[id][1];
            lr[id][0] = lr[id][1] = node();
            slist[pos[id]] = 0;
            bool c1 = S.find(in1) != S.end();
            bool c2 = S.find(in2) != S.end();
            if(c1 && c2)
            {
                int s = in1.s, t = in2.t;
                int lid = in1.lid, rid = in2.rid;
                it = S.emplace(s, t, lid, rid).first;
                lr[lid][1] = (*it);
                lr[rid][0] = (*it);
                S.erase(in1);
                S.erase(in2);
            }else{
                int s = pos[id], t = pos[id];
                int lid = slist[s-1], rid = slist[t+1];
                if(c1)
                {
                    s = in1.s;
                    lid = in1.lid;
                }
                if(c2)
                {
                    t = in2.t;
                    rid = in2.rid;
                }
                it = S.emplace(s, t, lid, rid).first;
                lr[lid][1] = (*it);
                lr[rid][0] = (*it);
                if(c1)
                    S.erase(in1);
                if(c2)
                    S.erase(in2);
            }
            pos[id] = 0;
//            printSet(S);
        }
    }
    return 0;
}
