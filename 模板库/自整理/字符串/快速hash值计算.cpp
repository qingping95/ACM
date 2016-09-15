//快速hash值计算
//一般修改为unsigned long long会比较准确
//一定要记得将模数从自然溢出修改为模质数，常用的大质数：1125899839733759LL， base/MAGIC：9987
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
//快速hash值计算
