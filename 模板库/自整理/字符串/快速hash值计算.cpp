//����hashֵ����
//һ���޸�Ϊunsigned long long��Ƚ�׼ȷ
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