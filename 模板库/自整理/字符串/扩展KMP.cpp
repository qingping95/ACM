//求S的所有后缀与T的最长公共前缀（存储在extand中）

void GetNext(const char* T, int* nxt)
{
    int len = strlen(T), a = 0;
    nxt[0] = len;
    while(a<len-1 && T[a] == T[a+1]) a++;
    nxt[1] = a;
    a = 1;
    for(int k=2;k<len;k++){
        int p = a + nxt[a] - 1, L = nxt[k - a];
        if(k - 1 + L >= p){
            int j = max(0, p-k+1);
            while(k+j<len && T[k+j] == T[j]) j++;
            nxt[k] = j;a = k;
        }else nxt[k] = L;
    }
}
void GetExtand(const char* S, const char* T, int* nxt, int* extand)
{
    GetNext(T, nxt);
    int slen = strlen(S), tlen = strlen(T), a = 0;
    int Minlen = min(slen, tlen);
    while(a < Minlen && S[a] == T[a]) a++;
    extand[0] = a;
    a = 0;
    for(int k=1;k<slen;k++){
        int p = a + extand[a] - 1, L = nxt[k-a];
        if(k-1+L >= p){
            int j = max(0, p-k+1);
            while(k+j < slen && j < tlen && S[k+j] == T[j]) j++;
            extand[k] = j; a = k;
        }else extand[k] = L;
    }
}