/*
* 这是一个lex识别程序
*/

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
typedef pair<int,int> PII;
const int INF=0x3f3f3f3f;
void Open()
{
    #ifndef ONLINE_JUDGE
        freopen("F:/in.txt","r",stdin);
        //freopen("F:/my.txt","w",stdout);
    #endif // ONLINE_JUDGE
}

class LEX {
public :
	void Main()
	{
		string str = " ";
		string tempString = " ";
		char ch = 0;
		int charCount = 0;
		int wordCount = 0;
		int lineCount = 0;
        freopen("测试数据.txt", "r", stdin);
		string tmp = "";
		while(getline(cin, tmp)) str += tmp, str += '\n', lineCount++;
		printf("测试文本为:\n");
		cout<<str<<endl;
		int m = 0;
		str += ' ';
		for (int i = 0; i < str.length(); i++)
		{
            // 1:关键字 2:函数名/变量名/类名 3:数字 4:运算符 5:分隔符
			switch (m)
			{
			case 0:
				ch = str[i];
				if (ch == '+' || ch == '-' || ch == '*' || ch == '/'
						|| ch == '=' || ch == '>' || ch == '<' || ch == '&'
						|| ch == '|' || ch == '^' || ch == '%') {
					tempString = "";
					tempString += ch;
					m = 4;
				} else if (ch == ',' || ch == ';' || ch == '{' || ch == '}'
						|| ch == '(' || ch == ')') {
					m = 5;
				} else if (isdigit(ch = str[i])) {
					tempString = "";
					tempString += ch;
					m = 3;
				} else if (isalpha(ch = str[i])) {
					tempString = "";
					tempString += ch;
					m = 2;
				} else {
				}
				break;

			case 4:
				ch = str[i];
				if(tempString.compare("/") == 0 && ( ch =='/')){
					int startIndex = i-1;
					while(str[i]!='\n'){
						i++;
					}
					cout<<"< 注释为: "<<"“ "<<str.substr(startIndex,i)<<" ” >"<<endl;
					m=0;
				}else if(tempString.compare("/") == 0 && ( ch =='*')){
					int startIndex = i-1;
					i++;
					while(true){
						if(str[i]=='*' && str[i+1] =='/'){
                            cout<<"< 注释为: "<<"“ "<< str.substr(startIndex,i+2)<<" ” >"<<endl;
							break;
						}else{
							i++;
						}
					}
					i++;
					m=0;
				}else if (ch == '+' || ch == '-' || ch == '=' || ch == '>' || ch == '<' || ch == '&'
						|| ch == '|' ) {
					tempString += ch;
				}else {
					if(tempString.length()==1
							|| tempString.compare("++")==0
							|| tempString.compare("--")==0
							|| tempString.compare("+=")==0
							|| tempString.compare("-=")==0
							|| tempString.compare(">=")==0
							|| tempString.compare("<=")==0
							|| tempString.compare("<<")==0
							|| tempString.compare(">>")==0
							|| tempString.compare("*=")==0
							|| tempString.compare("/=")==0
							|| tempString.compare("&&")==0
							|| tempString.compare("||")==0) {
                        cout<<"< 运算符 " << "“ " << tempString << " ” >"<<endl;
						charCount++;
					}
					i--;
					m = 0;
				}
				break;

			case 5:
				i--;
				cout<<"< 分隔符 " << "“ " << ch << " ” >"<<endl;
				charCount++;
				m = 0;
				break;

			case 2:
				if (isalpha(ch = str[i])) {
					tempString += ch;
				} else {
					if (isKeyWord(tempString)) {
                        cout<<"< 关键字 " << "“ " << tempString<< " ” >"<<endl;
						wordCount++;
					} else {
					    cout<<"< 函数名/变量名/类名 " << "“ " << tempString << " ” >"<<endl;
						wordCount++;
					}
					i--;
					m = 0;
				}
				break;

			case 3:
				if (isdigit((ch = str[i]))) {
					tempString += ch;
				} else {
				    cout<<"< 数字 " << "“ " << tempString << " ” >"<<endl;
					wordCount++;
					i--;
					m = 0;
				}
				break;
			}
		}
		printf("该测试文本的单词个数为 %d \n" , wordCount);
		printf("该测试文本的字符个数为 %d \n" , charCount);
		printf("该测试文本的行数为 %d \n", lineCount);
	}
	bool isKeyWord(string str) {
		if (str.compare("void")==0 || str.compare("if")==0 || str.compare("for")==0 || str.compare("while")==0
        || str.compare("do")==0 || str.compare("return")==0 || str.compare("break")==0 || str.compare("main")==0
        || str.compare("int")==0 || str.compare("char")==0 || str.compare("public")==0 || str.compare("static")==0
        || str.compare("string")==0
        || str.compare("private")==0 || str.compare("throws")==0 || str.compare("boolean")==0 || str.compare("true")==0
        || str.compare("false")==0 || str.compare("new")==0 || str.compare("case")==0 || str.compare("class")==0) {
			return true;
		} else
			return false;
	}
};


int main()
{
    //Open();
    LEX lex;
    lex.Main();
    return 0;
}
