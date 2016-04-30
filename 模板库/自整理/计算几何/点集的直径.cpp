int diameter2(Point* points, int n, Point* p)
{
    n = ConvexHull(points, n, p);
    if(n == 1) return 0;
    if(n == 2) return Dot(p[1] - p[0], p[1] - p[0]);
    p[n] = p[0];
    int ans = 0;
    for(int u = 0, v = 1; u<n; u++)
	// һ��ֱ����ס��p[u]-p[u+1]
        while(true)
        {
      // ��Area(p[u], p[u+1], p[v+1]) <= Area(p[u], p[u+1], p[v])ʱֹͣ��ת
      // ��Cross(p[u+1]-p[u], p[v+1]-p[u]) - Cross(p[u+1]-p[u], p[v]-p[u]) <= 0
      // ����Cross(A,B) - Cross(A,C) = Cross(A,B-C)
      // �����Cross(p[u+1]-p[u], p[v+1]-p[v]) <= 0
            int diff = Cross(p[u+1]-p[u], p[v+1]-p[v]);
            if(diff <= 0)
            {
                ans = max(ans, (int)(Dot(p[u]-p[v], p[u]-p[v])+eps));//u��v�Ƕ����
                if(diff == 0) ans = max(ans, (int)(Dot(p[u]-p[v+1], p[u]-p[v+1])+eps));// diff == 0ʱu��v+1Ҳ�Ƕ����
                break;
            }
            v = (v+1)%n;
        }
    return ans;
}