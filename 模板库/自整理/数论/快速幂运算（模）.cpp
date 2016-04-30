//快速幂运算（模）
int mod_pow(int x,int n)
{
    int res=1;
    while(n>0)
    {
        if(n&1) res=(long long)res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
//快速幂运算（模）

//如果乘法可能爆long long的话， 使用下面的板子
ll mul(ll a,ll b){
    return ((a*b-ll(((long double)a)/mod*b+1e-3)*mod)%mod+mod)%mod;
}
ll pow_mod(ll a, ll n) {
    a%=mod;
    ll r = 1;
    while(n) {
        if(n&1) r = mul(r,a);
        a=mul(a,a);
        n>>=1;
    }
    return r;
}