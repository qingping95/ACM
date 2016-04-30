int diameter2(Point* points, int n, Point* p)
{
    n = ConvexHull(points, n, p);
    if(n == 1) return 0;
    if(n == 2) return Dot(p[1] - p[0], p[1] - p[0]);
    p[n] = p[0];
    int ans = 0;
    for(int u = 0, v = 1; u<n; u++)
	// 一条直线贴住边p[u]-p[u+1]
        while(true)
        {
      // 当Area(p[u], p[u+1], p[v+1]) <= Area(p[u], p[u+1], p[v])时停止旋转
      // 即Cross(p[u+1]-p[u], p[v+1]-p[u]) - Cross(p[u+1]-p[u], p[v]-p[u]) <= 0
      // 根据Cross(A,B) - Cross(A,C) = Cross(A,B-C)
      // 化简得Cross(p[u+1]-p[u], p[v+1]-p[v]) <= 0
            int diff = Cross(p[u+1]-p[u], p[v+1]-p[v]);
            if(diff <= 0)
            {
                ans = max(ans, (int)(Dot(p[u]-p[v], p[u]-p[v])+eps));//u和v是对踵点
                if(diff == 0) ans = max(ans, (int)(Dot(p[u]-p[v+1], p[u]-p[v+1])+eps));// diff == 0时u和v+1也是对踵点
                break;
            }
            v = (v+1)%n;
        }
    return ans;
}