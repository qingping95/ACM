struct Item{
        int key,val,nxt;
};
struct UMP{
        Item item[555555];
        int itnum;
        int head[999997];
        int MOD;
        UMP(){
                MOD=999997;
                clear();
        }
        void clear(){
                memset(head,-1,sizeof(head));
                itnum=0;
        }
		bool find(int x)
		{
			int idx=x%MOD;
			for(int i=head[idx]; i!=-1; i=item[i].nxt)
			{
				if(item[i].key==x) return item[i].val;
			}
			return -1;//没找到
		}
        int& operator[](int x){
                int idx=x%MOD;
                //cerr<<idx<<endl;
                for(int i=head[idx];i!=-1;i=item[i].nxt){
                        if(item[i].key==x) return item[i].val;
                }
                item[itnum]=(Item){x,0,head[idx]};
                head[idx]=itnum;
                return item[itnum++].val;
        }
};