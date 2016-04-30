//
int prime[N];
int pn;
void get_prime()
{
    for(int i=2;i<N;i++)
    {
        if(vis[i]) continue;
        prime[pn++]=i;
        for(int j=i;j<N;j+=i)
        {
            vis[j]=1;
        }
    }
}
//ÆÓËØÉ¸ËØÊý

//--------------------O(n)É¸·¨------------------------//
bool pvis[N];
int pri[N];
int prin;
void getpri(){
    prin = 0;
    memset(pvis, 0, sizeof(pvis));
    for(int i = 2; i < N; i++) {
        if(pvis[i] == 0) pri[prin++] = i;
        for(int j = 0; j < prin && (long long)pri[j]*i < N; j++) {
            pvis[pri[j]*i] = 1;
            if(i % pri[j] == 0) break;
        }
    }
}