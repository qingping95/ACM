//二分最佳完美匹配//
/*下标从1开始，需要对nx，ny赋值，并不需要初始化其中的任何数组*/
/*如果求最大匹配，那么权值不变，如果求最小匹配，那么权值变为负数。*/
//const int N = 101;
const int INF = 0x3f3f3f3f;
//const double EPS = 1e-9;
typedef int w_type;  /////权值的类型，int or double
w_type w[N][N],lx[N],ly[N],slack[N];     //顶标,权值矩阵
int linky[N],linkx[N];  //二分匹配的对象
bool visx[N],visy[N];    //访问数组
int nx,ny;              //x集合的大小nx，y集合的大小ny
bool find(int x)
{
    visx[x] = true;
    for(int y = 1; y <= ny; y++)
    {
        if(visy[y]) continue;
        w_type t = lx[x] + ly[y] - w[x][y];
        //if(fabs(t) < EPS) //(double)t==0
        if( t==0 ) //(int)t==0
        {
            visy[y] = true;
            if(linky[y]==-1 || find(linky[y]))
            {
                linky[y] = x;
                linkx[x] = y;
                return true;        //找到增广轨
            }
        }
        else slack[y] = min(t,slack[y]);
    }
    return false;                   //没有找到增广轨（说明顶点x没有对应的匹配，与完备匹配(相等子图的完备匹配)不符）
}
w_type KM()                //返回最优匹配的值
{
    int i,j;
    memset(linky,-1,sizeof(linky));
    memset(linkx,-1,sizeof(linkx));
    memset(ly,0,sizeof(ly));
    for(i = 1; i <= nx; i++)
        for(j = 1,lx[i] = -INF; j <= ny; j++)
            lx[i]=max(w[i][j],lx[i]);
			/* if(w[i][j] > lx[i])
                lx[i] = w[i][j]; */
    for(int x = 1; x <= nx; x++)
    {
        for(i = 1; i <= ny; i++) slack[i] = INF;
        while(true)
        {
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(find(x)) break;				//找到增广轨，退出
            w_type d = INF;
            for(i = 1; i <= ny; i++)        //没找到，对l做调整(这会增加相等子图的边)，重新找
                if(!visy[i]) d = min(d,slack[i]);
            for(i = 1; i <= nx; i++)
                if(visx[i]) lx[i] -= d;
            for(i = 1; i <= ny; i++)
                if(visy[i]) ly[i] += d;
        }
    }
	//以下为判断是否完全匹配的代码。
	//如下，-INF为权值矩阵的初始值。返回值可根据情况修改如下图，-INF为权值矩阵的初始值。
	//返回值可根据情况修改，一般情况可删除。
    // for(int i = 1; i <= ny; i++)
        // if(w[linky[i]][i] == -INF)
            // return 1;
    w_type result = 0;
    for(i = 1; i <= ny; i++)
    if(linky[i]>-1)
        result += w[linky[i]][i];
    return result;
}

/*
*		//如果想要检查是否完全匹配，则需要遍历linkx或linky数组。
*        for(int i=1;i<=nx;i++)
*            for(int j=1;j<=ny;j++)
*            {
*                w[i][j] = -x[i].Distance(y[j]);
*            }
*        KM();
*        for(int i=1;i<=nx;i++)
*        {
*            printf("%d\n",linkx[i]);
*        }
*/
