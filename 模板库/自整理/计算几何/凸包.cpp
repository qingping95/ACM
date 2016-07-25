/*
* ����͹�������������Ϊp������Ϊn�����������Ϊch������͹��������
* ���벻�����ظ��㣬��Ϊ��ʹcrossʧȥ���á�����ִ����֮��sort�����ƻ�˳��
* �����ϣ����͹���ı���������㣬������ <= ��Ϊ <
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
* �÷���
*        for(int i=0;i<n;i++)
*        {
*            double x,y;
*            scanf("%lf%lf",&x,&y);
*            p[i] = (Point){x,y};
*        }
*        int bagNum=ConvexHull(p,n,tubag);
*/