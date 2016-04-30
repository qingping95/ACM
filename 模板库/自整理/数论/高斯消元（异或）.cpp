int cal(int row) //��˹��Ԫ�У���num-row������Ԫ��ö������Ԫ֮����������ش�����
{
    for(int i=row-1;i>=0;i--)
    {
        ans[i] = mat[i][num];
        for(int j=i+1;j<num;j++)
            ans[i]^=mat[i][j]*ans[j];
    }
    int rnt = 0;
    //ö������Ԫ֮��Ĳ���
    for(int i=0;i<num;i++)
        rnt += ans[i];

    return rnt;
}
int gauss(int ty)
{
    init(ty);//��ʼ��ϵ������
    int row = 0, col = 0;
    while(row < num && col < num)
    {
        int i;
        for(i = row; i<num; i++)
            if(mat[i][col]) break;
        if(i == num){
            col++;continue;
        }
        if(i != row)// ������н�������ͨ��˹��Ԫ��ͬ���������Ϊ�����Ǿ���
        {
            for(int j = col; j <= num;j++)
                swap(mat[i][j], mat[row][j]);
        }
        if(row != col)// ������н�����Ϊ�˽�����Ԫ�ƶ������棬���㴦��
        {
            for(int j=0;j<num;j++)
                swap(mat[j][row], mat[j][col]);
        }
        for(int i = row + 1; i < num; i++)
        {
            if(mat[i][row] == 0) continue;
            for(int j = row; j <= num; j++)
                mat[i][j] ^= mat[row][j];
        }
        row++, col++;
    }
    for(int i = row; i < num; i++) // �������ȫ0�еĽ���Ƿ�Ϊ1�����Ϊ1�����޽�
        if(mat[i][num]) return -1;

    // ö������Ԫ
    int free = num - row;
    int len = 1<<free;
    int rnt = INF;
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < free; j++)
            ans[num - j - 1] = ((i >> j) & 1);
        rnt = min(rnt , cal(row));
    }
    return rnt;
}