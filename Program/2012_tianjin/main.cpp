#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
//#include <unordered_map>
#define N 100010
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-10;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
int up[4] = {9, 9, 9, 7};
int til[4][11];//
int tmp[4][11];//
char str[33], c[11];//
int f[333];//
char ans[7777][11];//
PII sta[15];//
int vis[(1<<13)+10];
bool judge(int x, int y)
{
    memcpy(tmp, til, sizeof(til));
    sta[13] = PII(x, y);
    tmp[x][y]++;
//    int cnt = 0;
    bool flag = true;
    for(int i = 0; i < 14 && flag; i++)
    {
        if(tmp[sta[i].first][sta[i].second] != 2) flag = false;
    }
    if(flag) return true;
    flag = true;
    for(int i = 0; i < 3 && flag; i++)
        if(tmp[i][1] && tmp[i][9]){
            tmp[i][1] --, tmp[i][9]--;
        }else{
            return false;
        }
    for(int j = 1; j <= 7 && flag; j++)
        if(tmp[3][j]){
            tmp[3][j]--;
        }else{
            return false;
        }
    if(flag == false) return false;
    for(int i = 0; i < 3 && flag; i++)
        if(tmp[i][1] || tmp[i][9]) return true;
    for(int j = 1; j <= 7 && flag; j++)
        if(tmp[3][j]) return true;
    return false;
}
int dfs(int num)
{
    if(num == 0) return true;
    if(vis[num] != -1) return vis[num];
    for(int k = 0; k < 13; k++)
    {
        if(!(num & (1 << k))) continue;
//        if(vis[k]) continue;
        int i = sta[k].first, j = sta[k].second;
        if(til[i][j] == 0) continue;
        if(__builtin_popcount(num) == 2){
            if(til[i][j] == 2) return vis[num] = true;
        }else{
            if(til[i][j] >= 3){
                til[i][j] -= 3;
                int ns = num;
                for(int l = 0, cnt = 0; l < 13 && cnt < 3; l++)
                    if((num & (1 << l)) && sta[l] == PII(i,j))  ns ^= (1 << l), cnt++;
                if(dfs(ns)){
                    til[i][j] += 3;
                    return vis[num] = true;
                }
                til[i][j] += 3;
            }
            if(i != 3 && j+2 <= up[i] && til[i][j+1] && til[i][j+2]){
                bool flag1 = false, flag2 = false, flag3 = false;
                int ns = num;
                til[i][j]--, til[i][j+1]--, til[i][j+2] --;
                for(int l = 0; l < 13; l++){
                    if(!(num & (1 << l))) continue;
                    if(!flag1 && sta[l] == PII(i,j))   ns ^= (1 << l), flag1 = true;
                    else if(!flag2 && sta[l] == PII(i,j+1)) ns ^= (1 << l), flag2 = true;
                    else if(!flag3 && sta[l] == PII(i,j+2)) ns ^= (1 << l), flag3 = true;
                }
                if(dfs(ns)){
                    til[i][j]++, til[i][j+1]++, til[i][j+2] ++;
                    return vis[num] = true;
                }
                til[i][j]++, til[i][j+1]++, til[i][j+2]++;
            }
        }
    }
    return vis[num] = false;
}
int main()
{
//    Open();
    f['m'] = 0, f['s'] = 1, f['p'] = 2, f['c'] = 3;
    c[0] = 'm', c[1] = 's', c[2] = 'p', c[3] = 'c';
    int T;scanf("%d", &T);
    while(T--)
    {
        memset(til, 0, sizeof(til));
        memset(vis, -1, sizeof(vis));
        for(int i = 0; i < 13; i++)
        {
            scanf("%s", str);
            til[f[str[1]]][str[0] - '0'] ++;
            sta[i] = PII(f[str[1]], str[0] - '0');
        }
        int limit = 1 << 13;
//        for(int i = 0; i < 13; i ++)
//        {
//            int ns = (limit-1)^(1<<i);
//            til[sta[i].first][sta[i].second]--;
//            dfs(ns);
//            for(int j = i+1; j < 13; j++){
//                til[sta[j].first][sta[j].second]--;
//                dfs(ns ^ (1 << j));
//                til[sta[j].first][sta[j].second]++;
//            }
//            til[sta[i].first][sta[i].second]++;
//        }
        int tail = 0;
        for(int i = 0; i < 4; i++)
            for(int j = 1; j <= up[i]; j++)
            {
                if(til[i][j] >= 4) continue;
                bool flag = false;
                if(til[i][j] || (i != 3 && j-1 >= 1 && til[i][j-1]) || (i != 3 && j+1 <= up[i] && til[i][j+1])) flag = true;
                if(judge(i, j))
                {
                    ans[tail][0] = j+'0';
                    ans[tail][1] = c[i];
                    ans[tail++][2] = '\0';
                    flag = false;
                }
                if(flag)
                {
                    bool res = false;
                    if(til[i][j] && !res){
                        int ns = limit - 1;
                        for(int l = 0, cnt = 0; l < 13 && cnt < 1; l++)
                            if(sta[l] == PII(i,j))  ns ^= (1 << l), cnt++;
                        til[i][j]--;
                        res = dfs(ns);
                        til[i][j]++;
                    }
                    if(til[i][j] >= 2 && !res){
                        int ns = limit-1;
                        for(int l = 0, cnt = 0; l < 13 && cnt < 2; l++)
                            if(sta[l] == PII(i,j))  ns ^= (1 << l), cnt++;
                        til[i][j] -= 2;
                        res = dfs(ns);
                        til[i][j] += 2;
                    }
                    if(i != 3 && !res && j-2 >= 1 && til[i][j-2] && til[i][j-1])
                    {
                        int ns = limit - 1;
                        bool flag1 = false, flag2 = false;
                        for(int l = 0; l < 13; l++)
                        {
                            if(!flag1 && sta[l] == PII(i,j-1))   ns ^= (1 << l), flag1 = true;
                            else if(!flag2 && sta[l] == PII(i,j-2)) ns ^= (1 << l), flag2 = true;
                        }
                        til[i][j-2]--, til[i][j-1]--;
                        res = dfs(ns);
                        til[i][j-2]++, til[i][j-1]++;
                    }
                    if(i != 3 && !res && j-1 >= 1 && j+1 <= up[i] && til[i][j-1] && til[i][j+1])
                    {
                        int ns = limit - 1;
                        bool flag1 = false, flag2 = false;
                        for(int l = 0; l < 13; l++)
                        {
                            if(!flag1 && sta[l] == PII(i,j-1))   ns ^= (1 << l), flag1 = true;
                            else if(!flag2 && sta[l] == PII(i,j+1)) ns ^= (1 << l), flag2 = true;
                        }
                        til[i][j+1]--, til[i][j-1]--;
                        res = dfs(ns);
                        til[i][j+1]++, til[i][j-1]++;
                    }
                    if(i != 3 && !res && j + 2 <= up[i] && til[i][j+2] && til[i][j+1])
                    {
                        int ns = limit - 1;
                        bool flag1 = false, flag2 = false;
                        for(int l = 0; l < 13; l++)
                        {
                            if(!flag1 && sta[l] == PII(i,j+2))   ns ^= (1 << l), flag1 = true;
                            else if(!flag2 && sta[l] == PII(i,j+1)) ns ^= (1 << l), flag2 = true;
                        }
                        til[i][j+2]--, til[i][j+1]--;
                        res = dfs(ns);
                        til[i][j+2]++, til[i][j+1]++;
                    }
                    if(res)
                    {
                        ans[tail][0] = j+'0';
                        ans[tail][1] = c[i];
                        ans[tail++][2] = '\0';
                    }
                }
            }
        if(tail == 0){
            printf("Nooten\n");
        }else{
            printf("%d", tail);
            for(int i = 0; i < tail; i++)
                printf(" %s", ans[i]);
            printf("\n");
        }
    }
    return 0;
}
