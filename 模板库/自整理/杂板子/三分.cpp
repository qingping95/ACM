double Calc(Type a)
{
    /* 根据题目的意思计算 */
}

void Solve(void)
{
    double Left, Right;
    double mid, midmid;
    double mid_value, midmid_value;
    Left = MIN; Right = MAX;
    while (Left + EPS < Right)
    {
        mid = (Left + Right) / 2;
        midmid = (mid + Right) / 2;
        mid_area = Calc(mid);
        midmid_area = Calc(midmid);
        // 假设求解最大极值.
        if (mid_area >= midmid_area) Right = midmid;
        else Left = mid;
    }
}