double Calc(Type a)
{
    /* ������Ŀ����˼���� */
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
        // ����������ֵ.
        if (mid_area >= midmid_area) Right = midmid;
        else Left = mid;
    }
}