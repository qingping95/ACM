#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int N = 250;

// ���鼯ά��
int belong[N];
int findb(int x) {
    return belong[x] == x ? x : belong[x] = findb(belong[x]);
}
void unit(int a, int b) {
    a = findb(a);
    b = findb(b);
    if (a != b) belong[a] = b;
}

int n, match[N];
vector<int> e[N];
int Q[N], rear;
int next_[N], mark[N], vis[N];

// �����㷨��ĳ�׶���������������x, y�������������r
int LCA(int x, int y) {
    static int t = 0; t++;
    while (true) {
        if (x != -1) {
            x = findb(x); // ��Ҫ��Ӧ����Ӧ�Ļ���ȥ
            if (vis[x] == t) return x;
            vis[x] = t;
            if (match[x] != -1) x = next_[match[x]];
            else x = -1;
        }
        swap(x, y);
    }
}

void group(int a, int p) {
    while (a != p) {
        int b = match[a], c = next_[b];

        // next������������ǻ����е�·���ģ��ۺ�match�������ã�ʵ�����γ���
        // ˫��������(x, y)��ƥ��ģ�next[x]��next[y]�Ϳ���ָ���������ˡ�
        if (findb(c) != p) next_[c] = b;

        // �滷�еĵ㶼�л��������ҵ�ƥ�䣬���Զ�Ҫ��ǳ�S�͵�ӵ�������ȥ��
        // ���ڵ�ƥ�����ѱ��ͣ������Щ�����ֻ����ƥ��ɹ�һ���㣬��aug��
        // ÿ��ƥ�䵽һ�����break��ֹ�˵�ǰ�׶ε������������½׶εı������
        // �������ģ�����������Ϊ�˱�֤��һ�㡣
        if (mark[b] == 2) mark[Q[rear++] = b] = 1;
        if (mark[c] == 2) mark[Q[rear++] = c] = 1;

        unit(a, b); unit(b, c);
        a = c;
    }
}

// ����
void aug(int s) {
    for (int i = 0; i < n; i++) // ÿ���׶ζ�Ҫ���±��
        next_[i] = -1, belong[i] = i, mark[i] = 0, vis[i] = -1;
    mark[s] = 1;
    Q[0] = s; rear = 1;
    for (int front = 0; match[s] == -1 && front < rear; front++) {
        int x = Q[front]; // ����Q�еĵ㶼��S�͵�
        for (int i = 0; i < (int)e[x].size(); i++) {
            int y = e[x][i];
            if (match[x] == y) continue; // x��y��ƥ�䣬����
            if (findb(x) == findb(y)) continue; // x��yͬ��һ�仨������
            if (mark[y] == 2) continue; // y��T�͵㣬����
            if (mark[y] == 1) { // y��S�͵㣬�滷����
                int r = LCA(x, y); // rΪ��i��j��s��·���ϵĵ�һ�������ڵ�
                if (findb(x) != r) next_[x] = y; // r��x����ͬһ�����䣬next��ǻ�����·��
                if (findb(y) != r) next_[y] = x; // r��y����ͬһ�����䣬next��ǻ�����·��

                // ������r -- x - y --- r���滷���ɵ㣬r��Ϊ������ı�ǽڵ㣬�൱�������еĳ����ڵ�
                group(x, r); // ��·��r --- xΪ��
                group(y, r); // ��·��r --- yΪ��
            }
            else if (match[y] == -1) { // y���ɣ��������㣬R12������
                next_[y] = x;
                for (int u = y; u != -1; ) { // ������ȡ��
                    int v = next_[u];
                    int mv = match[v];
                    match[v] = u, match[u] = v;
                    u = mv;
                }
                break; // �����ɹ����˳�ѭ����������һ�׶�
            }
            else { // ��ǰ�����Ľ�����+y+match[y]�γ��µĽ���������match[y]���������Ϊ���ѽڵ�
                next_[y] = x;
                mark[Q[rear++] = match[y]] = 1; // match[y]Ҳ��S�͵�
                mark[y] = 2; // y��ǳ�T��
            }
        }
    }
}

bool g[N][N];
int main() {
        freopen("perfect.in","r",stdin);
        freopen("perfect.out","w",stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) g[i][j] = false;

    // ��ͼ��˫���
    for(int i=0;i<n;i++){
                int num;scanf("%d",&num);
                for(int j=0;j<num;j++){
                        int x;scanf("%d",&x);
                        g[i][x-1]=true;
                }
    }
    for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        if(g[i][j]==true && g[j][i]==true){
                                e[i].push_back(j), e[j].push_back(i);
                        }else{
                                g[i][j]=g[j][i]=false;
                        }
                }
    }


//  int x, y; while (scanf("%d%d", &x, &y) != EOF) {
//      x--, y--;
//      if (x != y && !g[x][y])
//          e[x].push_back(y), e[y].push_back(x);
//      g[x][y] = g[y][x] = true;
//  }

    // ����ƥ��
    for (int i = 0; i < n; i++) match[i] = -1;
    for (int i = 0; i < n; i++) if (match[i] == -1) aug(i);

    // �����
    int tot = 0;
    for (int i = 0; i < n; i++) if (match[i] != -1) tot++;
//  printf("%d\n", tot);
//  for (int i = 0; i < n; i++) if (match[i] > i)
//      printf("%d %d\n", i + 1, match[i] + 1);
        if(tot==n){
                puts("YES");
        }else{
                puts("NO");
        }
    return 0;
}