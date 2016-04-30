//�����������ƥ��//
/*�±��1��ʼ����Ҫ��nx��ny��ֵ��������Ҫ��ʼ�����е��κ�����*/
/*��������ƥ�䣬��ôȨֵ���䣬�������Сƥ�䣬��ôȨֵ��Ϊ������*/
//const int N = 101;
const int INF = 0x3f3f3f3f;
//const double EPS = 1e-9;
typedef int w_type;  /////Ȩֵ�����ͣ�int or double
w_type w[N][N],lx[N],ly[N],slack[N];     //����,Ȩֵ����
int linky[N],linkx[N];  //����ƥ��Ķ���
bool visx[N],visy[N];    //��������
int nx,ny;              //x���ϵĴ�Сnx��y���ϵĴ�Сny
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
                return true;        //�ҵ������
            }
        }
        else slack[y] = min(t,slack[y]);
    }
    return false;                   //û���ҵ�����죨˵������xû�ж�Ӧ��ƥ�䣬���걸ƥ��(�����ͼ���걸ƥ��)������
}
w_type KM()                //��������ƥ���ֵ
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
            if(find(x)) break;				//�ҵ�����죬�˳�
            w_type d = INF;
            for(i = 1; i <= ny; i++)        //û�ҵ�����l������(������������ͼ�ı�)��������
                if(!visy[i]) d = min(d,slack[i]);
            for(i = 1; i <= nx; i++)
                if(visx[i]) lx[i] -= d;
            for(i = 1; i <= ny; i++)
                if(visy[i]) ly[i] += d;
        }
    }
	//����Ϊ�ж��Ƿ���ȫƥ��Ĵ��롣
	//���£�-INFΪȨֵ����ĳ�ʼֵ������ֵ�ɸ�������޸�����ͼ��-INFΪȨֵ����ĳ�ʼֵ��
	//����ֵ�ɸ�������޸ģ�һ�������ɾ����
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
*		//�����Ҫ����Ƿ���ȫƥ�䣬����Ҫ����linkx��linky���顣
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
