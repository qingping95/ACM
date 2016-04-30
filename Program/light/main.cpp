    #include <iostream>
    #include <string.h>
    #include <cstdio>
    using namespace std;
    const int MAXN = 101;
    const int MAXE = 5000;
    struct node
    {
           int v, w, next;
    }mapp[MAXE];
    int id;
    int head[MAXN];
    int tempmap[MAXN][MAXN];
    void init()
    {
         id = 0;
         memset(head, -1, sizeof(head));
    }
    void addedge(int u, int v, int val)
    {
         mapp[id].v = v, mapp[id].w = val, mapp[id].next = head[u], head[u] = id ++;

         mapp[id].v = u, mapp[id].w = 0, mapp[id].next = head[v], head[v] = id ++;
    }
    const int inf = 1<<29;
    int cur[MAXN], dist[MAXN], pre[MAXN], gap[MAXN];
    int SAP(int s, int e, int n)
    {
        memcpy(cur, head, sizeof(head));
        memset(dist, 0, sizeof(dist));
        memset(gap, 0, sizeof(gap));
        int u, v;
        int flow = 0;
        int bottle = inf;
        gap[s] = n;
        u = pre[s] = s;
        bool flag = true;
        while (dist[s] < n){
              flag = false;
              for (int &j = cur[u]; j != -1; j = mapp[j].next){
                  v = mapp[j].v;
                  if (mapp[j].w > 0 && dist[v]+1 == dist[u]){
                     flag = true;
                     if (mapp[j].w < bottle){
                        bottle = mapp[j].w;
                     }
                     pre[v] = u;
                     u = v;
                     if (u == e){
                        flow += bottle;
                        while (u != s){
                              u = pre[u];
                              mapp[cur[u]].w -= bottle;
                              mapp[cur[u]^1].w += bottle;
                        }
                        bottle = inf;
                     }
                     break;
                  }
              }
              if (flag) continue;
              int mindis = n;
              for (int j = head[u]; j != -1; j = mapp[j].next){
                  v = mapp[j].v;
                  if (mapp[j].w > 0 && mindis > dist[v]){
                     mindis = dist[v], cur[u] = j;
                  }
              }
              if (!(--gap[dist[u]])){
                 break;
              }
              gap[dist[u] = mindis+1] ++;
              u = pre[u];
        }
        return flow;
    }

    int n;
    void floyd()
    {
         for (int k = 1; k <= n; k ++){
             for (int i = 1; i <= n; i ++){
                 for (int j = 1; j <= n; j ++){
                     if (tempmap[i][j] > tempmap[i][k]+tempmap[k][j] && i != j){
                        tempmap[i][j] = tempmap[i][k]+tempmap[k][j];
                     }
                 }
             }
         }
    }
    int a[MAXE], b[MAXE];
    int main()
    {
        freopen("/home/qingping/in.txt", "r", stdin);
        int m, k;
        while (scanf("%d%d%d", &n, &m, &k) && (n+m+k)){
              init();
              for (int i = 1; i <= n; i ++){
                  for (int j = 1; j <= n; j ++)tempmap[i][j] = inf;
                  tempmap[i][i] = 0;
              }
              for (int i = 0; i < m; i ++){
                  int a1, b1;
                  scanf("%d%d", &a1, &b1);
                  tempmap[a1][b1] = 1;
              }
              int kao = 0;
              for (int i = 1; i <= n; i ++){
                  for (int j = 1; j <= n; j ++){
                      if (tempmap[i][j] == 1){
                         a[kao] = i;
                         b[kao ++] = j;
                      }
                  }
              }
              floyd();
              for (int i = 0; i < kao; i ++){
                  if (tempmap[1][a[i]]+tempmap[b[i]][n] < k){
                        addedge(a[i]+n, b[i], inf);
                        cout<<a[i]<<" "<<b[i]<<endl;
                  }
              }
              for (int i = 1; i <= n; i ++)addedge(i, i+n, 1);
              int ans = SAP(n+1, n, 2*n);

              if (ans == inf)printf("%d\n", n);
              else
                  printf("%d\n", ans);
        }
        return 0;
    }
