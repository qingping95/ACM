map<int,int>mp;  
int a[N],tot,n,q;  
int T[M],lson[M],rson[M],val[M];  
int bulid(int l,int r){  
    int root=tot++;  
    val[root]=0;  
    int m=(l+r)>>1;  
    if(l!=r){  
        lson[root]=bulid(l,m);  
        rson[root]=bulid(m+1,r);  
    }  
    return root;  
}  
int update(int root,int pos,int v){  
    int newroot=tot++,tmp=newroot;  
    int l=1,r=n;  
    val[newroot]=val[root]+v;  
    while(l<r){  
        int m=(l+r)>>1;  
        //���µ�ʱ����Ҫ���������ʷ��Ϣ  
        //����ԭ����������������������  
        if(pos<=m){  
            lson[newroot]=tot++;rson[newroot]=rson[root];  
            newroot=lson[newroot];root=lson[root];  
            r=m;  
        }  
        //����������  
        else{  
            rson[newroot]=tot++;lson[newroot]=lson[root];  
            newroot=rson[newroot];root=rson[root];  
            l=m+1;  
        }  
        val[newroot]=val[root]+v;  
    }  
    return tmp;  
}  
int query(int root,int pos){  
    int ret=0;  
    int l=1,r=n;  
    while(pos<r){  
        int m=(l+r)>>1;  
        if(pos<=m){  
            r=m;  
            root=lson[root];  
        }  
        else{  
            ret+=val[lson[root]];  
            root=rson[root];  
            l=m+1;  
        }  
    }  
    return ret+val[root];  
}  
int main(){  
    while(scanf("%d",&n)!=EOF){  
        tot=0;   //�����  
        for(int i=1;i<=n;i++)  
            scanf("%d",&a[i]);  
        T[n+1]=bulid(1,n);  
        for(int i=n;i;i--){  
            int nxt;  
            map<int,int>::iterator it=mp.find(a[i]);  
            if(it==mp.end()) nxt=n+1;  
            else nxt=it->second;  
            //������ǵ�һ�γ��֣�Ҳ�������һ��λ���ϣ���ֱ�Ӹ���  
            if(nxt>n)  
                T[i]=update(T[i+1],i,1);  
            //��ԭ����λ���ϲ������ڵ�ǰλ�ø���  
            else{  
                int t=update(T[i+1],nxt,-1);  
                T[i]=update(t,i,1);  
            }  
            mp[a[i]]=i;  
        }  
        scanf("%d",&q);  
        while(q--){  
            int l,r;  
            scanf("%d%d",&l,&r);  
            printf("%d\n",query(T[l],r));  
        }  
    }  
    return 0;  
}  