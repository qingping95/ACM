//欧拉函数：求小于n的有多少个数与n互质O(sqrt(n))，
//这里根据代码逻辑，似乎可以先打出质数表，利用质数表的话效率会更高才对
//O(sqrt(n))
int phi(int n)
{
    int res=n,a=n;
     for(int i=2;i*i<=a;i++){
         if(a%i==0){
             res=res/i*(i-1);//先进行除法是为了防止中间数据的溢出
             while(a%i==0) a/=i;
         }
     }
     if(a>1) res=res/a*(a-1);
     return res;
}
//先打质数表的版本，复杂度O(logn)
bool vis[N];
int pri[N];
int pt;
void getpri()
{
    pt = 0;
	for(int i = 2; i < N; i++)
	{
		if(vis[i]) continue;
		pri[pt++] = i;
        for(int j = i; j < N; j += i) vis[j] = 1;
	}
}
int phi(int n)
{
     int res=n,a=n;
     for(int i=0;pri[i]*pri[i]<=a;i++){
         if(a%pri[i]==0){
             res=res-res/pri[i];//先进行除法是为了防止中间数据的溢出
             while(a%pri[i]==0) a/=pri[i];
         }
     }
     if(a>1) res=res-res/a;
     return res;
}
//欧拉函数：求小于n的有多少个数与n互质

//筛法欧拉函数，复杂度与素数表一样
int euler[N];
void getEuler(int UP)
{
	memset(euler, 0, sizeof(euler));
	euler[1] = 1;
	for(int i = 2; i <= UP; i++)
	{
		if(!euler[i])
		{
			for(int j = i; j <= UP; j += i)
			{
				if(!euler[j]) euler[j] = j;
				euler[j] = euler[j] / i * (i-1);
			}
		}
	}
}
//筛法欧拉函数

///O(N)  
void linear_phi_table2()  
{  
    int i, j, k = 0;  
    for (i = 2; i < mx; i++)  
    {  
        if (!unprime[i]) ///若i为素数，phi(i)=i-1  
        {  
            prime[k++] = i;  
            phi[i] = i - 1;  
        }  
        for (j = 0; j < k && prime[j] * i < maxn; j++)  
        {  
            unprime[prime[j] * i] = true;  
            if (i % prime[j]) ///若i和p互素，则phi(i*p) = phi(i) * phi(p) = phi(i) * (p-1)  
                phi[prime[j] * i] = phi[i] * (prime[j] - 1);  
            else  
            {  
                ///此时有i=kp，则  
                ///phi(p*kp) = phi(k*p^2) = p*phi(kp)  
                phi[prime[j] * i] = phi[i] * prime[j];  
                break;  
            }  
        }  
    }  
}  