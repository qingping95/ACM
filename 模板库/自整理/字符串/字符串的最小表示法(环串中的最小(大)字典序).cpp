//HDU 5442

#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
#define N 100010
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
        freopen("D:/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
//kind = 1 表示找出符合条件的最小坐标，否则为最大坐标
int smallestRepresation(char s[], int n, bool kind)
{
    for(int tt = 0; tt < n; tt++) s[n + tt] = s[tt];
    s[n * 2] = '\0';
    int i, j, k ,l;
    for(i = 0, j = 1; j < n;){
        for(k = 0; k < n && s[i+k] == s[j+k]; k++);
        if(k >= n) {
            if(kind) //求相同字典序的出现的最小坐标
                break;
            i = j;j ++; //求相同字典序的出现的最大坐标..
			//不过这里效率并不高，效率比较高的方法还是找出符合串之后用字符串匹配算法求出最大坐标比较好
            continue;
        }
        if(s[i+k] < s[j+k]) j += k + 1;//这里是最大表示法(即字典序最大， 最小只需要将大于改为小于即可)
        else {
            l = i+k;
            i = j;
            j = max(l, j) + 1;
        }
    }
    return i;
}
char s[42222], s1[42222], s2[42222];
int main()
{
    Open();
    int T;scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        scanf("%s", s);
        strcpy(s1, s);
        strcpy(s2, s);
        int shunidx = smallestRepresation(s1, n, 1);
        reverse(s2, s2+n);
        int liidx = smallestRepresation(s2, n, 0);
        liidx = n - liidx - 1;
        int kind = -1;
        int cnt = 0;
        for(int i = shunidx, j = liidx; cnt < n; cnt++){
            if(s[i] != s[j]){
                kind = (s[i] < s[j]);
                break;
            }
            i++, j--;
            i = i % n;
            j = (j + n) % n;
        }
        if(kind == -1){
            if(shunidx <= liidx){
                printf("%d 0\n", shunidx+1);
            }else if(shunidx > liidx){
                printf("%d 1\n", liidx+1);
            }
        }else{
            if(kind == 0) printf("%d %d\n", shunidx+1, kind);
            else printf("%d %d\n", liidx+1, kind);
        }
    }
    return 0;
}
