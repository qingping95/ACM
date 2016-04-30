int fac[]={1,1,2,6,24,120,720,5040,40320,362880};   //康拖展开判重
//         0!1!2!3! 4! 5!  6!  7!   8!    9!
int Cantor(int s[],n){        //康拖展开求该序列的hash值
    int sum=0;
    for(int i=0;i<n;i++){
        int cnt=0;
        for(int j=i+1;j<n;j++)
            if(s[i]>s[j])
                cnt++;
        sum+=(cnt*fac[n-i-1]);
    }
    return sum;
}
void invCantor(int ans[], int n, int k)  
{  
    int vis[20] = {0};
    int i, j, t; 
    for (i = 0; i < n; ++i)  
    {  
        t = k / fac[n - i - 1];  
        for (j = 1; j <= n; j++)  
            if (!vis[j])  
            {  
                if (t == 0) break;  
                --t;  
            }  
        ans[i] = j, vis[j] = true;  
        k %= fac[n - i - 1];///余数  
    }  
}