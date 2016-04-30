void dfs(){  
    stack<pair<int,pair<int,int> > >s;  
    s.push(mp(1,mp(0,0)));  
    while(!s.empty()){  
        pair<int,pair<int,int> >now=s.top();s.pop();  
        int u=now.first,pre=now.second.first,i=now.second.second;  
        if(i==0){  
            int t=++depth;  
            b[++tot]=t;  
            f[t]=u;  
            p[u]=tot;  
        }  
        if(i<edge[u].size()){  //重点是这里
            int v=edge[u][i].first,w=edge[u][i].second;  
            s.push(mp(u,mp(pre,i+1)));  
            if(v==pre) continue;  
            dist[v]=dist[u]+w;  
            s.push(mp(v,mp(u,0)));  
        }      
        else   
            b[++tot]=b[p[pre]];  
    }  
}
//大概是一个用bfs求图中各个点的dfs序的代码。