#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const int N = 10010;
const int MAGIC = 31;
char str[N];
unordered_map<ULL, int> m;
struct word
{
    char ori[1111];
    char cur[1111];
    ULL hvalue;
    void update(int id)
    {
        strcpy(cur, ori);
        int len = strlen(cur);
        for(int i = 0; i < len; i++)
            cur[i] = tolower(cur[i]);
        //reverse(cur, cur+strlen(cur));
        //cout<<cur<<endl;
        len = strlen(cur);
        hvalue = 0;
        for(int i = 1; i <= len;i++)
            hvalue = hvalue * MAGIC + cur[i-1] - 'a';
        m[hvalue] = id;
    }
}s[N*10];
int pre[N], sta[N*10];
int main()
{
    //Open();
    memset(pre, -1, sizeof(pre));
    int len = 0;
    scanf("%d", &len);
    scanf("%s", str);
//    strcpy(sss, str);
//    reverse(sss, sss+len);
//    cout<<str<<endl;
//    cout<<sss<<endl;
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%s", s[i].ori);
        s[i].update(i);
    }
    //init_hash(str, h, len);
    for(int i = 0; i < len; i++)
    {
        ULL ch = 0;
        for(int j = i; j >= max(0, i-1001); j--)
        {
            ch = ch * MAGIC + str[j] - 'a';
            if(m.find(ch) != m.end() && (j == 0 || pre[j-1] != -1))
                pre[i] = m[ch];
        }
    }
    int tail = 0;
    int idx = len-1;
    while(idx >= 0)
    {
        sta[tail++] = pre[idx];
        //if(idx + 1 == strlen(s[pre[idx]].cur)) break;
        idx -= strlen(s[pre[idx]].ori);

    }
    for(int i = tail-1; i>= 0; i--)
        printf("%s%c", s[sta[i]].ori, " \n"[i == 0]);
    return 0;
}
