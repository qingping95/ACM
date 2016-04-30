int cal(int row) //高斯消元中，有num-row个自由元，枚举自由元之后计算结果，回代过程
{
    for(int i=row-1;i>=0;i--)
    {
        ans[i] = mat[i][num];
        for(int j=i+1;j<num;j++)
            ans[i]^=mat[i][j]*ans[j];
    }
    int rnt = 0;
    //枚举自由元之后的操作
    for(int i=0;i<num;i++)
        rnt += ans[i];

    return rnt;
}
int gauss(int ty)
{
    init(ty);//初始化系数矩阵
    int row = 0, col = 0;
    while(row < num && col < num)
    {
        int i;
        for(i = row; i<num; i++)
            if(mat[i][col]) break;
        if(i == num){
            col++;continue;
        }
        if(i != row)// 这里的行交换和普通高斯消元相同，将矩阵变为上三角矩阵
        {
            for(int j = col; j <= num;j++)
                swap(mat[i][j], mat[row][j]);
        }
        if(row != col)// 这里的列交换是为了将自由元移动到后面，方便处理
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
    for(int i = row; i < num; i++) // 检测所有全0行的结果是否为1，如果为1，则无解
        if(mat[i][num]) return -1;

    // 枚举自由元
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