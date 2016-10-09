//����hashֵ����
//һ���޸�Ϊunsigned long long��Ƚ�׼ȷ
//һ��Ҫ�ǵý�ģ������Ȼ����޸�Ϊģ���������õĴ�������1125899839733759LL�� base/MAGIC��9987
//�������̫���ˣ������˱�LL�����ǻ���һ��int��ģ���ȽϺ�
//998244353
//1004535809
//985661441
//880803841
//786433
//100000007
//200000033
//300000007
//400000009
//500000009
//600000007
//699999953
//799999999
//900000053
//1000000007
inline void init_hash(char *s, unsigned int *h, int l)
{
    h[0]= 0;
    for(int i = 1; i <= l;++i)
        h[i] = h[i-1] * MAGIC + s[i-1];
    base[0] = 1;
    for(int i = 1; i <= l; ++i)
        base[i] = base[i-1] * MAGIC;
}
inline unsigned int string_hash(unsigned *h, int l, int r) //[0-base)
{
    return h[r] - h[l]* base[r-l];
}
//����hashֵ����

//����hashֵ����
//һ���޸�Ϊunsigned long long��Ƚ�׼ȷ
//һ��Ҫ�ǵý�ģ������Ȼ����޸�Ϊģ���������õĴ�������1125899839733759LL�� base/MAGIC��9987
const LL MOD = 1e9+7.5;
const LL MAGIC = 9987;
LL h[N], base[N];
inline void init_hash(char *s, LL *h, int l)
{
    h[0]= 0;
    for(int i = 1; i <= l;++i)
        h[i] = (h[i-1] * MAGIC % MOD + s[i-1])%MOD;
    base[0] = 1;
    for(int i = 1; i <= l; ++i)
        base[i] = base[i-1] * MAGIC % MOD;
}
inline LL string_hash(LL *h, int l, int r) //[0-base)
{
    return (h[r] - h[l]* base[r-l]%MOD+MOD)%MOD;
}

