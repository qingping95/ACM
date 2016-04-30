
//KMP算法
void GetNextval(char* T, int nxt[])  
{  
    nxt[0] = -1;
    int tlen = strlen(T), j=0, k=-1;
    while(j<tlen)
        if(k == -1 || T[j] == T[k]) nxt[++j] = ++k;
        else k = nxt[k];
}
int KmpSearch(char* s, char* p)  
{  
    int i = 0;  
    int j = 0;  
    int sLen = strlen(s);  
    int pLen = strlen(p);  
    while (i < sLen && j < pLen)  
    {  
        //①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++      
        if (j == -1 || s[i] == p[j])  
        {  
            i++;  
            j++;  
        }  
        else
            j = next[j];  
    }  
    if (j == pLen)  
        return i - j;  
    else  
        return -1;  
}  
//KMP算法

//统计次数：
void GetNextval(int* p, int n, int nxt[])
{
    int pLen = n;
    nxt[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen )
    {
        //p[k]表示前缀，p[j]表示后缀
        if (k == -1 || p[j] == p[k])
        {
            ++j;
            ++k;
            //较之前next数组求法，改动在下面4行
            if (p[j] != p[k] || j==pLen)
                nxt[j] = k;   //之前只有这一行
            else
                //因为不能出现p[j] = p[nxt[j]]，所以当出现时需要继续递归，k = nxt[k] = nxt[nxt[k]]
                nxt[j] = nxt[k];
        }
        else
        {
            k = nxt[k];
        }
    }
}
int KmpSearch(int* s, int ns, int* p, int ps)
{
    if(ns < ps) return 0;
    int i = 0;
    int j = 0;
    int sLen = ns;
    int pLen = ps;
    int cnt=0;
    int tmp=0;
    while (i < sLen)
    {
        //①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            //②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = nxt[j]
            //nxt[j]即为j所对应的next值
            j = nxt[j];
        }
        if (j == pLen)
        {
            cnt++;
            j = nxt[j];
        }
    }
    return cnt;
}
//统计次数(int)

int nxt[N];
char s[N];
char t[N];
int vis[N];
int sum[N];
 
void GetNextval(char* p, int nxt[])
{
    int pLen = strlen(p);
    nxt[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen )
    {
        //p[k]表示前缀，p[j]表示后缀
        if (k == -1 || p[j] == p[k])
        {
            ++j;
            ++k;
            //较之前next数组求法，改动在下面4行
            if (p[j] != p[k])
                nxt[j] = k;   //之前只有这一行
            else
                //因为不能出现p[j] = p[nxt[j]]，所以当出现时需要继续递归，k = nxt[k] = nxt[nxt[k]]
                nxt[j] = nxt[k];
        }
        else
        {
            k = nxt[k];
        }
    }
}
void KmpSearch(char* s, char* p)
{
    int i = 0;
    int j = 0;
    int sLen = strlen(s);
    int pLen = strlen(p);
    while (i < sLen )
    {
        //①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            //②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = nxt[j]
            //nxt[j]即为j所对应的next值
            j = nxt[j];
        }
        if(j==pLen)
        {
            vis[i-pLen]=true;
            j=nxt[j];
        }
    }
}
//统计数目（char）