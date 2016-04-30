//////////////最佳完美匹配KM算法//////////////////
//下标从1开始。设置w,lx,ly,slack的类型。所有变量无需清零，仅w需要重新赋值
//有slack数组的O(n^3) 版本
int n;//点数
double w[MAXN][MAXN];//边权
double lx[MAXN],ly[MAXN],slack[MAXN];//顶标
int s[MAXN],t[MAXN],left_[MAXN];

int match(int i)
{
    s[i] = 1;
    for(int j = 1;j <= n;j++)
        if(!t[j])
        {
                double tmp=lx[i]+ly[j]-w[i][j];
                if( fabs(tmp) < EPS)
                {
                    t[j] = 1;
                    if(!left_[j] || match(left_[j]))
                    {
                        left_[j] = i;
                        return 1;
                    }
                }
                else slack[j] = min(tmp,slack[j]);
        }
    return 0;
}

void update()
{
    double a = INF;
    for(int i = 1;i <= n;i++)
        if(!t[i]) a = min(a,slack[i]);
    for(int i = 1;i <= n;i++)
    {
        if(s[i]) lx[i] -= a;
        if(t[i]) ly[i] += a;
    }
}

void km()
{
    for(int i = 1;i <= n;i++)
    {
        left_[i] = ly[i] = 0;
        lx[i] = -INF;
        for(int j = 1;j <= n;j++)
            lx[i] = max(lx[i],w[i][j]);
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++)
            slack[j] = INF;
        while(1)
        {
            for(int j = 1;j <= n;j++) s[j] = t[j] = 0;
            if(match(i)) break;
            else update();
        }
    }
}
/*how to use
for(int i = 1;i <= n;i++)
    for(int j = 1;j <= n;j++)
        w[i][j] = -cal_dis(i,j);//赋权
km();
for(int i = 1;i <= n;i++)
    printf("%d\n",left_[i]);
*/
//////////////最佳完美匹配KM算法//////////////////