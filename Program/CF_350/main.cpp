#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
typedef pair<char,int> PCI;
const LL INF=0x3f3f3f3f3f3f3f3fLL;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
const LL N = 1000010;
char sb[N];
char s[N];
char ans1[N];
char ans2[N];
int num[111];
bool update(int res, int add)
{
    bool can = true;
    int tmp = res;
    while(tmp)
    {
        num[tmp%10]+=add;
        if(num[tmp%10]<0) can = false;
        tmp /= 10;
    }
    if(!can)
    {
        while(res)
        {
            num[res%10]-=add;
            res /= 10;
        }
    }
    return can;
}
int main()
{
//    Open();
    scanf("%s%s", s, sb);
    int n = strlen(s);
    for(int i = 0; i < n; i++)
        num[s[i]-'0']++;
    int m = strlen(sb);
    bool flag = true;
    for(int i = 1; i < m; i++)
    {
        if(sb[i] == sb[i-1]) continue;
        if(sb[i] < sb[i-1]){
            flag = false;
            break;
        }
        if(sb[i] > sb[i-1])
        {
            break;
        }
    }
    for(int i = 0; i < m; i++)
        num[sb[i]-'0']--;
    if(n == 1 && s[0] == '0') printf("0\n");
    else if(n == 2 && s[0] == '0' && s[1] == '0') printf("0\n");
    else {
        bool FLAG = true;
        for(int len = 6, ten = 100000; len >= 1; len--, ten /= 10)
        {
            int idx = 0;
            int res = n - len;
            if(res < ten) continue;
            if(!update(res, -1)) continue;
            int fir = 1;
            while(fir < 10 && num[fir] == 0) fir++;
            bool h1 = false;
            bool h2 = false;
            if(fir >= sb[0] - '0' && sb[0] != '0')
            {
                for(int j = 0; j < m; j++)
                    ans1[idx++] = sb[j];
                for(int i = 0 ; i < 10; i++)
                    while(num[i]--)
                        ans1[idx++] = '0'+i;
                ans1[idx++] = '\0';
                h1 = true;
                memset(num, 0, sizeof(num));
                for(int i = m; i < idx-1; i++)
                    num[ans1[i]-'0']++;
            }
            if(fir < 10)
            {
                idx = 0;
                num[fir]--;
                ans2[idx++] = fir+'0';
                for(int i = 0; i < 10; i++){
                    if(i + '0' == sb[0] && flag == false){
                        for(int j = 0; j < m; j++)
                            ans2[idx++] = sb[j];
                    }
                    while(num[i]--)
                        ans2[idx++] = '0'+i;
                    if(i + '0' == sb[0] && flag){
                        for(int j = 0; j < m; j++)
                            ans2[idx++] = sb[j];
                    }
                }
                ans2[idx++] = '\0';
                h2 = true;
            }
            char* out = NULL;
            if(h1&&h2)
            {
                out = ans1;
                for(int i = 0; i < res; i++)
                {
                    if(ans1[i] < ans2[i]) {out = ans1;break;}
                    if(ans1[i] > ans2[i]) {out = ans2;break;}
                }
            }
            else if(h1) out = ans1;
            else if(h2) out = ans2;
            if(out != NULL)
            {
                printf("%s\n", out);
                FLAG = false;
                break;
            }

            update(res, 1);
        }
        if(FLAG)
            printf("0\n");
    }
    return 0;
}
