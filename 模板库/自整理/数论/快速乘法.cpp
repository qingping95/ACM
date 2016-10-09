//两个大数相乘爆long long，但是相加不会爆
LL mul(LL x, LL y)
{
	LL ret = 0;
	while(y)
	{
		if(y & 1) ret = (ret+x) %mod;
		x = (x+x)%mod;
		y >>= 1;
	}
	return ret;
}
