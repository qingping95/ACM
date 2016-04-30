#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <climits>
using namespace std;
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define VINT vector<int>
#define PII pair<int,int>
#define MP(x,y) make_pair((x),(y))
#define ll long long
#define ull unsigned long long
#define MEM0(x)  memset(x,0,sizeof(x))
#define MEM(x,val) memset((x),val,sizeof(x))
#define scan(x) scanf("%d",&(x))
#define scan2(x,y) scanf("%d%d",&(x),&(y))
#define scan3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z))
#define scan4(x,y,z,k) scanf("%d%d%d%d",&(x),&(y),&(z),&(k))
#define Max(a,b) a=max(a,b)
#define Min(a,b) a=min(a,b)
#define fuck(x) cout<<#x<<" - "<<x<<endl
const double EPS = 1e-10;
double A[441][441];
double b[441];
double B[441][445];
double x[441];
int t;
void gauss_jordan(){
    int n = t;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            B[i][j] = A[i][j];
        }
    }
    for(int i=0;i<n;i++) B[i][n] = b[i];
    for(int i=0;i<n;i++){
        int pivot = i;
        for(int j=i;j<n;j++){
            if(abs(B[j][i]) > abs(B[pivot][i]) ) pivot = j;
        }
        swap(B[i],B[pivot]);
        if(abs(B[i][i]) < EPS)
            return;

        for(int j=i+1;j<=n;j++) B[i][j] /= B[i][i];
        for(int j=0;j<n;j++){
            if(i != j){
                for(int k=i+1; k<=n;k++) B[j][k] -= B[j][i] * B[i][k];
            }
        }
    }
    for(int i=0;i<n;i++) x[i] = B[i][n];
}
int ID[444][444];
int main()
{
    //freopen("in.txt","r",stdin);
    t = 0;
    for(int i = 0; i < 21; i++)
        for(int j = 0; j <= i; j ++)
            ID[i][j] = ID[j][i] = t++;
    double P;
    while(scanf("%lf",&P) == 1){
        memset(A,0,sizeof(A));
        memset(b,0,sizeof(b));
        for(int i=0;i<=19;i++){
            for(int j=0;j<=i;j++){
                int tmp = ID[i][j];
                int to1 = min(20,j+1);
                int to2 = max(0,j-2);
                A[tmp][tmp]+=1;
                A[tmp][ID[i][to1]]+=-P;
                A[tmp][ID[i][to2]]+=P-1;
                b[tmp] = 1;
            }
        }
        for(int i=0;i<=20;i++){
            A[ID[20][i]][ID[20][i]] = 1;
        }
        gauss_jordan();
        printf("%.9f\n",x[0]);
    }
    return 0;
}
