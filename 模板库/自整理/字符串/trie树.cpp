#include <iostream>  
#include <cstdio>  
#include <algorithm>  
#include <cstring>  
#define N 100010  
using namespace std;  
struct node  
{  
    long long nxt[2];//存储nxt节点在数组中的下标  
}trie[N*40];  
long long all_idx,bit[42],num[N],n;  
long long createNode()  
{  
    memset(trie[all_idx].nxt,-1,sizeof(trie[all_idx].nxt));//没有访问过的置为-1  
    return all_idx++;  
}  
void insert_Node(long long root,long long cur)  
{  
    memset(bit,0,sizeof(bit));//存储cur的二进制数  
    long long len=0;  
    while(cur)  
    {  
        bit[len++]=cur&1;  
        cur>>=1;  
    }  
    long long idx=root;  
    //将40位全部存进去  
    for(len=40;len>=0;len--)  
    {  
        long long k=bit[len];  
        if(trie[idx].nxt[k]==-1)  
            trie[idx].nxt[k]=createNode();  
        idx=trie[idx].nxt[k];  
    }  
}  
long long running(long long root,long long cur)  
{  
    long long sum=0;  
    memset(bit,0,sizeof(bit));  
    long long len=0;  
    while(cur)  
    {  
        bit[len++]=cur&1;  
        cur>>=1;  
    }  
    long long idx=root;  
    for(len=40;len>=0;len--)  
    {  
        long long k=!bit[len];/////两个数不相同，异或结果为1  
        if(trie[idx].nxt[k]!=-1) {  
            sum+=(1LL<<len);///////一定要加LL，被坑了好久。。。也是无语了  
            idx=trie[idx].nxt[k];  
        }  
        else idx=trie[idx].nxt[!k];//如果不存在这样的数，只能取0，并且从这边走下去。  
    }  
    return sum;  
}  
int main()  
{  
    scanf("%I64d",&n);  
    long long pre=0,post=0;  
    long long ans=0;  
    for(long long i=0;i<n;i++)  
        scanf("%I64d",num+i),pre^=num[i];  
    long long root=createNode();  
    for(long long i=n-1;i>=0;pre^=num[i],post^=num[i],i--)  
    {  
        insert_Node(root,post);  
        ans=max(ans,running(root,pre));  
    }  
    ans=max(ans,running(root,pre));//判断取0个前缀的时候的值  
    cout<<ans<<endl;  
    return 0;  
}  