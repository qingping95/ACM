#include <iostream>  
#include <cstring>  
#include <algorithm>  
#include <cstdio>  
#define N 1002  
using namespace std;  
const int kind=4;  
const int INF=0x3f3f3f;  
  
int allocp;  
int verID[100];  
int n,dp[N][N];  
char word[25],str[N];  
  
struct TrieNode  
{  
    int index;  
    bool unsafe;  
    TrieNode *next[kind];  
    TrieNode *fail;  
}memory[N],*q[N];  
  
TrieNode *createTrieNode()  
{  
    TrieNode *p=&memory[allocp];  
    p->index=allocp++;  
    p->fail=NULL;  
    p->unsafe=false;  
    memset(p->next,0,sizeof(p->next));  
    return p;  
}  
void insertTrieNode(TrieNode *pRoot,char s[])  
{  
    TrieNode *p=pRoot;  
    for(int i=0;s[i];i++)  
    {  
        int k=verID[s[i]];  
        if(p->next[k]==NULL)  
            p->next[k]=createTrieNode();  
        p=p->next[k];  
    }  
    p->unsafe=true;  
}  
  
void bulid_ac(TrieNode *pRoot)  
{  
    int head=0,tail=0;  
    TrieNode *p,*temp;  
    q[tail++]=pRoot;  
    pRoot->fail=NULL;  
    while(head<tail)  
    {  
        p=q[head++];  
        for(int i=0;i<kind;i++)  
        {  
            if(p->next[i]!=NULL)  
            {  
                if(p==pRoot)  
                    p->next[i]->fail=pRoot;  
                else  
                {  
                    p->next[i]->fail=p->fail->next[i];  
                    if(p->next[i]->fail->unsafe)  
                        p->next[i]->unsafe=true;  
                }  
                q[tail++]=p->next[i];  
            }  
            else// 由于需要在安全节点上找，所以如果没有这个next也要  
            {  
                if(p==pRoot)  
                    p->next[i]=pRoot;  
                else  
                    p->next[i]=p->fail->next[i];  
            }  
        }  
    }  
}  
  