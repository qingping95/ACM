const int MAXN = 100005;
const int MAXE = 200300;
struct Edge{
	int from,to,next;
	bool cut;
}edge[2*MAXE];
int head[MAXN],edgenum;
int Low[MAXN],DFN[MAXN],Stack[MAXN];//Belong数组的值是1~block
int dfn,top;
int Belong[MAXN],block;//新图的连通块标号（1~block）
bool Instack[MAXN];
int bridge; //割桥数量

void addedge(int u,int v){
	Edge E={u,v,head[u],0}; edge[edgenum]=E; head[u] = edgenum++;
	Edge E2={v,u,head[v],0};edge[edgenum]=E2;head[v] = edgenum++;
}
void Tarjan(int u,int pre){
	int v;
	Low[u] = DFN[u] = ++dfn;
	Stack[top++] = u;
	Instack[u] = true;
	for(int i = head[u]; ~i ;i = edge[i].next){
		v = edge[i].to;
		// 如果重边有效的话下面这句改成: if(v == pre && pre_num == 0){pre_num++;continue;} pre_num在for上面定义 int pre_num=0;
		if( v == pre )continue;
		if( !DFN[v] ){
			Tarjan(v,u);
			Low[u] = min(Low[u], Low[v]);
			if(Low[v] > DFN[u]){
				bridge++;
				edge[i].cut = true;
				edge[i^1].cut = true;
			}
		}
		else if(Instack[v])Low[u] = min(Low[u], DFN[v]);
	}
	if(Low[u] == DFN[u]){
		block++;
		do{
			v = Stack[--top];
			Instack[v] = false;
			Belong[v] = block;
		}while( v != u );
	}
}
void work(int l, int r){
	memset(DFN,0,sizeof(DFN));
	memset(Instack,false,sizeof(Instack));
	dfn = top = block = bridge = 0;
	for(int i = l; i <= r; i++)if(!DFN[i])Tarjan(i,i);
}
vector<int>G[MAXN];//点标从1-block
void suodian(){
	for(int i = 1; i <= block; i++)G[i].clear();
	for(int i = 0; i < edgenum; i+=2){
		int u = Belong[edge[i].from], v = Belong[edge[i].to];
		if(u==v)continue;
		G[u].push_back(v), G[v].push_back(u);
	}
}
void init(){edgenum = 0; memset(head,-1,sizeof(head));}
