//len[i] 记录的是回文串中心(i/2)到两端的最小距离
//       如果回文串长度为偶数，则回文中心为偏左的位置。
int len[N];
void manacher(char str[], int len[], int n)
{
    len[0] = 1;
    for(int i = 1, j = 0; i < (n<<1)-1; i++)
    {
        int p = i >> 1, q = i-p, r = ((j+1)>>1) + len[j] - 1;
        len[i] = r < q ? 0 : min(r-q+1, len[(j<<1)-i]);
        while(p > len[i]-1 && q + len[i] < n && str[p-len[i]] == str[q+len[i]])
            ++len[i];
        if(q + len[i] - 1 > r)
            j = i;
    }
}
//可以得到以idx/2为中心的串的左右端点。
PII getLR(int idx)
{
    int val = len[idx];
    if(idx&1){
        return PII(idx/2-val+1, idx/2+val);
    }else{
        return PII(idx/2-val+1, idx/2+val-1);
    }
}
