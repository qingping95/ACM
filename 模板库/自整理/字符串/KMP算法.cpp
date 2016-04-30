
//KMP�㷨
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
        //�����j = -1�����ߵ�ǰ�ַ�ƥ��ɹ�����S[i] == P[j]��������i++��j++      
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
//KMP�㷨

//ͳ�ƴ�����
void GetNextval(int* p, int n, int nxt[])
{
    int pLen = n;
    nxt[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen )
    {
        //p[k]��ʾǰ׺��p[j]��ʾ��׺
        if (k == -1 || p[j] == p[k])
        {
            ++j;
            ++k;
            //��֮ǰnext�����󷨣��Ķ�������4��
            if (p[j] != p[k] || j==pLen)
                nxt[j] = k;   //֮ǰֻ����һ��
            else
                //��Ϊ���ܳ���p[j] = p[nxt[j]]�����Ե�����ʱ��Ҫ�����ݹ飬k = nxt[k] = nxt[nxt[k]]
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
        //�����j = -1�����ߵ�ǰ�ַ�ƥ��ɹ�����S[i] == P[j]��������i++��j++
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            //�����j != -1���ҵ�ǰ�ַ�ƥ��ʧ�ܣ���S[i] != P[j]�������� i ���䣬j = nxt[j]
            //nxt[j]��Ϊj����Ӧ��nextֵ
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
//ͳ�ƴ���(int)

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
        //p[k]��ʾǰ׺��p[j]��ʾ��׺
        if (k == -1 || p[j] == p[k])
        {
            ++j;
            ++k;
            //��֮ǰnext�����󷨣��Ķ�������4��
            if (p[j] != p[k])
                nxt[j] = k;   //֮ǰֻ����һ��
            else
                //��Ϊ���ܳ���p[j] = p[nxt[j]]�����Ե�����ʱ��Ҫ�����ݹ飬k = nxt[k] = nxt[nxt[k]]
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
        //�����j = -1�����ߵ�ǰ�ַ�ƥ��ɹ�����S[i] == P[j]��������i++��j++
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            //�����j != -1���ҵ�ǰ�ַ�ƥ��ʧ�ܣ���S[i] != P[j]�������� i ���䣬j = nxt[j]
            //nxt[j]��Ϊj����Ӧ��nextֵ
            j = nxt[j];
        }
        if(j==pLen)
        {
            vis[i-pLen]=true;
            j=nxt[j];
        }
    }
}
//ͳ����Ŀ��char��