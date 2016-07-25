/*
* 计算凸包，输入点数组为p，个数为n，输出点数组为ch，返回凸包顶点数
* 输入不能有重复点，因为会使cross失去作用。函数执行完之后，sort，会破坏顺序
* 如果不希望在凸包的边上有输入点，把两个 <= 改为 <
*/

int ConvexHull(Point* p, int n, Point* ch)
{
    sort(p, p+n);
    int m = 0;
    for(int i=0;i<n;i++){
        while(m > 1 && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k=m;
    for(int i=n-2;i>=0;i--){
        while(m>k && Cross(ch[m-1] - ch[m-2], p[i] - ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n>1) m--;
    return m;
}

/*
* 用法：
*        for(int i=0;i<n;i++)
*        {
*            double x,y;
*            scanf("%lf%lf",&x,&y);
*            p[i] = (Point){x,y};
*        }
*        int bagNum=ConvexHull(p,n,tubag);
*/