#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
string prod[] = {
    "E`->E",
    "E->E+T",
    "E->E-T",
    "E->T",
    "T->T*F",
    "T->T/F",
    "T->F",
    "F->id",
    "F->(E)",
    "F->num"
};
map<int, int> act_s[20];//shift action
map<int, int> act_r[20];//reduce action
map<int, int> Goto[16]; //goto
int S[110000];  //analysis stack
int number[] = {1, 3, 3, 1, 3, 3, 1, 1, 3, 1};//number of each production
int prod_header[] = {'`', 'E', 'E', 'E', 'T', 'T', 'T', 'F', 'F', 'F'};
//left part of each production
string input;

//将输入中的id转换为a，num转换为b。
string pre_process(string str)
{
    string res = "";
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == 'i') res += 'a', i++;
        else if(str[i] == 'n') res += 'b', i+=2;
        else res += str[i];
    }
    return res+'$';
}
//make LR analysis table
void init()
{
    act_s[0]['('] = 5, act_s[0]['a'] = 4, act_s[0]['b'] = 6;
    act_s[1]['+'] = 7, act_s[1]['-'] = 8, act_s[1]['$'] = INF;
    act_s[2]['*'] = 9, act_s[2]['/'] = 10;
    act_s[5]['('] = 5, act_s[5]['a'] = 4, act_s[5]['b'] = 6;
    act_s[7]['('] = 5, act_s[7]['a'] = 4, act_s[7]['b'] = 6;
    act_s[8]['('] = 5, act_s[8]['a'] = 4, act_s[8]['b'] = 6;
    act_s[9]['('] = 5, act_s[9]['a'] = 4, act_s[9]['b'] = 6;
    act_s[10]['('] = 5, act_s[10]['a'] = 4, act_s[10]['b'] = 6;
    act_s[11][')'] = 16, act_s[11]['+'] = 7, act_s[11]['-'] = 8;
    act_s[12]['*'] = 9, act_s[12]['/'] = 10;
    act_s[13]['*'] = 9, act_s[13]['/'] = 10;

    act_r[2][')'] = 3, act_r[2]['+'] = 3,act_r[2]['-'] = 3, act_r[2]['$'] = 3;
    act_r[3][')'] = 6, act_r[3]['+'] = 6,act_r[3]['-'] = 6, act_r[3]['*'] = 6,act_r[3]['/'] = 6, act_r[3]['$'] = 6;
    act_r[4][')'] = 7, act_r[4]['+'] = 7,act_r[4]['-'] = 7, act_r[4]['*'] = 7,act_r[4]['/'] = 7, act_r[4]['$'] = 7;
    act_r[6][')'] = 9, act_r[6]['+'] = 9,act_r[6]['-'] = 9, act_r[6]['*'] = 9,act_r[6]['/'] = 9, act_r[6]['$'] = 9;
    act_r[12][')'] = 1, act_r[12]['+'] = 1,act_r[12]['-'] = 1, act_r[12]['$'] = 1;
    act_r[13][')'] = 2, act_r[13]['+'] = 2,act_r[13]['-'] = 2, act_r[13]['$'] = 2;
    act_r[14][')'] = 4, act_r[14]['+'] = 4,act_r[14]['-'] = 4, act_r[14]['*'] = 4,act_r[14]['/'] = 4, act_r[14]['$'] = 4;
    act_r[15][')'] = 5, act_r[15]['+'] = 5,act_r[15]['-'] = 5, act_r[15]['*'] = 5,act_r[15]['/'] = 5, act_r[15]['$'] = 5;
    act_r[16][')'] = 8, act_r[16]['+'] = 8,act_r[16]['-'] = 8, act_r[16]['*'] = 8,act_r[16]['/'] = 8, act_r[16]['$'] = 8;

    Goto[0]['E'] = 1, Goto[0]['T'] = 2, Goto[0]['F'] = 3;
    Goto[5]['E'] = 11, Goto[5]['T'] = 2, Goto[5]['F'] = 3;
    Goto[7]['T'] = 12, Goto[7]['F'] = 3;
    Goto[8]['T'] = 13, Goto[8]['F'] = 3;
    Goto[9]['F'] = 14;
    Goto[10]['F'] = 15;
}
//output information
void error()
{
    cout<<"该文法不属于算术表达式"<<endl;
}
void accept()
{
    cout<<"该语言已被算术表达式语言接受！"<<endl;
}
//output elements in stack
int print_stack(int tail)
{
    int res = 0;
    for(int i = 0; i < tail; i++)
    {
        if(S[i] == 'a') cout<<"id", res += 2;
        else if(S[i] == 'b') cout<<"num", res += 3;
        else if(S[i] <= 16) cout<<S[i], res+= (S[i] >= 10 ? 2 : 1);
        else cout<<(char)S[i], res++;
    }
    return res;
}
//print stable number space to console
void print_space(int num)
{
    for(int i = num; i < 25; i++)
        cout<<' ';
}
int main()
{
    freopen("F:/in.txt", "r", stdin);
//    freopen("F:/out.txt", "w", stdout);
    cin >> input;
    cout<<"data of input: "<<input<<endl;
    input = pre_process(input);
    cout<<"after transform: "<<input<<endl;
    cout<<"start analysis:"<<endl<<endl;
    init();
    int m = 0;
    int index = 0;
    int tail = 0;
    S[tail++] = 0;
    while(true)
    {
        int top = S[tail-1];
        if(act_s[top].find(input[index]) != act_s[top].end())
        {
            if(act_s[top][input[index]] == INF)
            {
                int num = print_stack(tail);
                print_space(num);
                cout<<"accept"<<endl;
                accept();
                break;
            }
            S[tail++] = input[index];
            S[tail++] = act_s[top][input[index]];
            index++;
            //output information
            int num = print_stack(tail);
            print_space(num);
            cout<<"shift "<<S[tail-1]<<endl;
        }
        else if(act_r[top].find(input[index]) != act_r[top].end())
        {
            int prod_index = act_r[top][input[index]];
            tail -= 2 * number[prod_index];
            top = S[tail-1];
            S[tail++] = prod_header[prod_index];
            S[tail++] = Goto[top][prod_header[prod_index]];
            //output information
            int num = print_stack(tail);
            print_space(num);
            cout<<"reduce by "<<prod[prod_index]<<endl;;
        }
        else
        {
            error();
            break;
        }
    }
    return 0;
}
