LL mul(LL a,LL b, LL c)
{
	LL ans=0;
	while(b){
		if(b&1)ans=(ans+a)%c;
		a=(a*2)%c;
		b>>=1;
	}
	return ans;
}
LL pow(LL x,LL n,LL mod)
{
	LL res=1;
	while(n>0){
		if(n&1)res=mul(res,x,mod);
		x=mul(x,x,mod);
		n>>=1;
	}
	return res;
}
bool test(LL nn,LL a,LL d)
{
    if(nn==1) return false;
    if(nn==2) return true;
    if(nn==a) return true;
    if((nn&1)==0)   return false;
    while(!(d&1))
        d=d>>1;
    LL t=pow(a,d,nn);
    while((d!=nn-1)&&(t!=1)&&(t!=nn-1))
    {
        t=mul(t,t,nn);
        d=d<<1;
    }
    return (t==nn-1||(d&1)==1);
}
bool isPrime(LL N)
{
    if(N<2)
        return false;
    LL a[]={2,3,61};//一些质数
    for(int i=0;i<=2;i++)//利用每个质数进行测试
    {
        if(!test(N,a[i],N-1))
            return false;
    }
    return true;
}