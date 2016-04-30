#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int INF=0x3f3f3f3f;
const double eps = 1e-10;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("/home/qingping/in.txt","r",stdin);
        //freopen("D:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}
char que[1111111];
int tail;
void read(string& s){
    tail=0;
    char pp = getchar();
    if(pp=='\n');
    else que[tail++] = pp;
    while(true){
        char c = getchar();
        que[tail++] = c;
        if(c=='>'){
            break;
        }
    }
    que[tail] = '\0';
    s = string(que);
    //cerr<<s<<endl;
}
int judge(string& s){
    if(s[0]=='<' && s[1]=='/') return 1;
    else if(s.length()>=2 && s[0]=='<' && s[s.length()-2]!='/') return 0;
    else return -1;
}
bool Match(string s1, string s2){
    return s1.length()>=2 && s2.length()>=3 && s1.substr(1).compare(s2.substr(2)) == 0;
}
string SOL(string s){
    tail=0;
    for(int i=0;i<s.length();i++){
        if(s[i]!=' ') que[tail++] = s[i];
        else break;
    }
    if(que[tail-1] == '>');
    else{
        que[tail++] = '>';
        que[tail]='\0';

    }
    return string(que);
}
int main()
{
    Open();
    int T;scanf("%d",&T);
    getchar();
    for(int Cas= 1;Cas<=T;Cas++){
        stack<string> stk;
        printf("Case #%d:\n", Cas);
        int spc=0;
        string lab;
        while(true){
            read(lab);
            //if(stk.size()>0) cerr<<stk.top()<<endl;
            if(lab[0]=='<'){
                spc = stk.size();
                if(stk.size()>0 && Match(stk.top(), lab)) stk.pop() , spc--;
                if(judge(lab) == 0) stk.push(SOL(lab));

                for(int i=0;i<spc;i++) printf(" ");
                printf("%s\n", lab.c_str());
                if(lab.compare(string("</html>")) == 0){
                    break;
                }
            }else{
                tail=0;
                int i;
                for(i=0;i<lab.length();i++){
                    if(lab[i]!='<') que[tail++] = lab[i];
                    else break;
                }
                que[tail]='\0';
                string word = string(que);
                for(int i=0;i<word.length();i++){
                    if(word[i]=='\n' || word[i]=='\t') word[i] = ' ';
                }
                for(int i=0;i<stk.size() ;i++) printf(" ");
                printf("%s\n", word.c_str());



                tail=0;
                for(;i<lab.length();i++) que[tail++] = lab[i];
                que[tail] = '\0';
                string label = string(que);

                spc = stk.size();
                if(stk.size() > 0 && Match(stk.top(), label)){
                    stk.pop();
                    spc--;
                }
                if(judge(label) == 0)
                    stk.push(SOL(label));

                for(int i=0;i<spc;i++) printf(" ");
                printf("%s\n", label.c_str());
                if(label.compare(string("</html>")) == 0){
                    break;
                }
            }
        }
    }
    return 0;
}
