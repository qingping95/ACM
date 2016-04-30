#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
//#include <unordered_map>
//#define lson x<<1
//#define rson x<<1|1
//#define mid ((lt[x].l+lt[x].r)/2)
//#define ID(x, y) ((x)*m+(y))
//#define CHECK(x, y) ((x)>=0 && (x)<n && (y)>=0 && (y)<m)
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("result_entity_relation.txt","r",stdin);
        freopen("F:/result_entity_relation.xml","w",stdout);
    #endif // ONLINE_JUDGE
}
string str;
vector<string> vec;
vector<string> split(string str, string pa)
{
    vector<string> res;
    int idx = 0;
    int slen = str.length();
    int plen = pa.length();

    while(idx < str.length())
    {
        int st = idx;
        while(idx < str.length() && str.substr(idx, plen).compare(pa) != 0) idx++;
        if(st != idx) res.push_back(str.substr(st, idx-st));
        idx += plen;
    }
    return res;
}
map<string, string> M;
struct people{
    int id;
    vector<string> company;
    vector<string> degree;
    vector<string> job;
    vector<string> school;
    void output()
    {
        cout<<"<rdf:Description"<<endl;
        cout<<" rdf:about=\"http://www.example.com\">"<<endl;
        cout<<"<people:id>"<<id<<"</people:id>"<<endl;
        printVec(company, "<people:company>");
        printVec(degree, "<people:degree>");
        printVec(job, "<people:job>");
        printVec(school, "<people:school>");
        cout<<"</rdf:Description>"<<endl;
        cout<<endl;
    }
    void printVec(vector<string> vec, string tag)
    {
        if(vec.size() == 0) return ;
        string closeTag = tag;
        closeTag.insert(1,"/");
        if(vec.size() == 1) {
            cout<<tag<<vec[0]<<closeTag;
        }else{
            cout<<tag<<endl;
            cout<<"<rdf:Bag>"<<endl;
            for(int i = 0; i < vec.size(); i ++)
            {
                cout<<"<rdf:li>"<<vec[i]<<"</rdf:li>"<<endl;
            }
            cout<<"</rdf:Bag>"<<endl;
            cout<<closeTag<<endl;
        }
    }
}info[111111];
int main()
{
    info[0].output();
    Open();
    while(cin>>str)
    {
        if(str[0] == '/') break;
        string tmp;
        cin >> tmp;
        M[str] = tmp;
    }
    while(getline(cin, str))
    {
        //cout<<str<<endl;
        if(str[0] == '*' && str[1] == '/') break;
    }
    int cur = 0;
    while(getline(cin, str))
    {
        if(str == "") continue;
        vec = split(str, "||");
        int idx = vec[0].find("::");
        idx += 2;
        int id = std::atoi(vec[0].substr(idx).c_str());
        info[id].id = id;
        cur = max(cur, id);

        idx = vec[1].find("::");
        string type = vec[1].substr(0, idx);
        type = M[type];
        //cout<<type<<endl;
        idx += 2;
        string value = vec[1].substr(idx);
        if(type == "company") info[id].company.push_back(value);
        if(type == "degree") info[id].degree.push_back(value);
        if(type == "job") info[id].job.push_back(value);
        if(type == "school") info[id].school.push_back(value);
    }
    cout<<"<?xml version=\"1.0\"?>"<<endl<<endl;
    cout<<"<rdf:RDF"<<endl;
    cout<<"xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"<<endl;
    cout<<endl;
    for(int i = 1; i <= cur; i++)
    {
        info[i].output();
    }
    cout<<"</rdf:RDF>"<<endl;
    return 0;
}
