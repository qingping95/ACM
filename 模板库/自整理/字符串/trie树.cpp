#include <iostream>  
#include <cstdio>  
#include <algorithm>  
#include <cstring>  
#define N 100010  
using namespace std;  
struct node  
{  
    long long nxt[2];//�洢nxt�ڵ��������е��±�  
}trie[N*40];  
long long all_idx,bit[42],num[N],n;  
long long createNode()  
{  
    memset(trie[all_idx].nxt,-1,sizeof(trie[all_idx].nxt));//û�з��ʹ�����Ϊ-1  
    return all_idx++;  
}  
void insert_Node(long long root,long long cur)  
{  
    memset(bit,0,sizeof(bit));//�洢cur�Ķ�������  
    long long len=0;  
    while(cur)  
    {  
        bit[len++]=cur&1;  
        cur>>=1;  
    }  
    long long idx=root;  
    //��40λȫ�����ȥ  
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
        long long k=!bit[len];/////����������ͬ�������Ϊ1  
        if(trie[idx].nxt[k]!=-1) {  
            sum+=(1LL<<len);///////һ��Ҫ��LL�������˺þá�����Ҳ��������  
            idx=trie[idx].nxt[k];  
        }  
        else idx=trie[idx].nxt[!k];//�������������������ֻ��ȡ0�����Ҵ��������ȥ��  
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
    ans=max(ans,running(root,pre));//�ж�ȡ0��ǰ׺��ʱ���ֵ  
    cout<<ans<<endl;  
    return 0;  
}  