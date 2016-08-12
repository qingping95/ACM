///用之前记得修改数据类型
///按照网上的写的，没有测试过正确性

///来源：http://www.chanmefang.com/?tag=fwt
///来源：http://picks.logdown.com/posts/179290-fast-walsh-hadamard-transform#
void fwt(LL *x, LL n, int op)  {
    int mm;
    for (mm = 1; mm < n; mm <<= 1)  { //2m
        for (int st = 0; st < n; st += mm << 1)
            for (LL i = 0; i < mm; i ++)  {
                LL a = x[st + i], b = x[st + i + mm];
                if(op == 1)x[st+i] = (a+b)%mod;
		else x[st+i] = (a-b)%mod;
                if(x[st+i] < 0) x[st+i] += mod;
		x[st+i+mm] = b;
            }
    }
}
