#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>

using namespace std;

const int maxn=100010;
const double eps=1e-6;

int n,nowx,ans;

bool able;

struct point
{
	int x,y;
	point(){}
	point(int a,int b)
	{
		x=a;y=b;
	}
	void init()
	{
		scanf("%d%d",&x,&y);
	}
	bool operator>(const point &a)const
	{
		return x>a.x || (x==a.x && y>a.y);
	}
	bool operator==(const point &o)const
	{
	    return x==o.x && y == o.y;
	}
};

struct segment
{
	int id;
	point p1,p2;
	segment(){}
	segment(int a,point b,point c)
	{
		id=a;
		p1=b;p2=c;
	}
	double calc()const
	{
		return p1.y+(p2.y-p1.y)*(nowx+eps-p1.x)/(p2.x+eps-p1.x);
	}
	bool operator<(const segment &a)const
	{
		return calc()<a.calc();
	}
	bool operator()(const segment &a)const
	{
		return calc()<a.calc();
	}
};

long long mul(const point &p1,const point &p2,const point &p3)
{
	return (long long)(p2.x-p1.x)*(p3.y-p1.y)-(long long)(p2.y-p1.y)*(p3.x-p1.x);
}

int sgn(long long x)
{
	return (x>0)-(x<0);
}

bool intersect(const segment &x1,const segment &x2)
{
	if (x1.id==x2.id) return false;
	if (min(x1.p1.x,x1.p2.x)>max(x2.p1.x,x2.p2.x)) return false;
	if (min(x1.p1.y,x1.p2.y)>max(x2.p1.y,x2.p2.y)) return false;
	if (max(x1.p1.x,x1.p2.x)<min(x2.p1.x,x2.p2.x)) return false;
	if (max(x1.p1.y,x1.p2.y)<min(x2.p1.y,x2.p2.y)) return false;
	long long a=mul(x1.p1,x1.p2,x2.p1);
   	long long b=mul(x1.p1,x1.p2,x2.p2);
	long long c=mul(x2.p1,x2.p2,x1.p1);
	long long d=mul(x2.p1,x2.p2,x1.p2);
	return sgn(a)*sgn(b)<=0 && sgn(c)*sgn(d)<=0;
}

map<segment,int> ma;

map<segment,int>::iterator Ins(segment s,int d)
{
    ma.insert(pair<segment, int>(s, d));
    map<segment,int>::iterator b = ma.find(s);
//	map<segment,int>::iterator b=ma.insert(pair<segment,int>(s,d));
	map<segment,int>::iterator a=b,c=b;
	a--;c++;
	if (intersect(a->first,b->first) || (intersect(b->first,c->first))) able=false;
	return b;
}

void Del(const map<segment,int>::iterator &b)
{
	map<segment,int>::iterator a=b,c=b;
	a--;c++;
	if (intersect(a->first,c->first)) able=false;
	ma.erase(b);
}

void update(const map<segment,int>::iterator p1,const map<segment,int>::iterator p2)
{
	map<segment,int>::iterator x=p1;
	x--;
	p1->second=x->second+1;
	p2->second=x->second;
	ans=max(ans,x->second+1);
}

struct triangle
{
	int id;
	point p1,p2,p3;
	map<segment,int>::iterator p12,p13,p23;
	triangle(){}
	triangle(point a,point b,point c)
	{
		p1=a;p2=b;p3=c;
	}
	void ins()
	{
		p12=Ins(segment(id,p1,p2),0);
		p13=Ins(segment(id,p1,p3),0);
		map<segment,int>::iterator x=p12;
		x++;
		if (x==p13) update(p12,p13);
		else update(p13,p12);
	}
	void help()
	{
		p23=Ins(segment(id,p2,p3),p12->second);
		Del(p12);
	}
	void del()
	{
		Del(p13);
		Del(p23);
	}
}tri[maxn];

struct rec
{
	int opt,x,id;
	rec(){}
	rec(int a,int b,int c)
	{
		opt=a;x=b;id=c;
	}
	bool operator<(const rec &a)const
	{
		return x<a.x || (x==a.x && opt<a.opt);
	}
}y[maxn*3];

int main()
{
	int test=0;
	while (~scanf("%d",&n))
	{
		if (n==-1) break;
		test++;
		printf("Case %d: ",test);
		ma.clear();
		ma.insert(pair<segment,int>(segment(0,point(-200000,-200000),point(200000,-200000)),1));
		ma.insert(pair<segment,int>(segment(0,point(-200000,200000),point(200000,200000)),1));
		int cnt=0;
		for (int a=1;a<=n;a++)
		{
			point p1,p2,p3;
			p1.init();
			p2.init();
			p3.init();
			if (p1>p2) swap(p1,p2);
			if (p1>p3) swap(p1,p3);
			if (p2>p3) swap(p2,p3);
			tri[a]=triangle(p1,p2,p3);
			tri[a].id=a;
			y[++cnt]=rec(1,p1.x,a);
			y[++cnt]=rec(2,p2.x,a);
			y[++cnt]=rec(3,p3.x,a);
		}
		sort(y+1,y+cnt+1);
		able=true;
		ans=1;
		for (int a=1;a<=cnt && able;a++)
		{
			nowx=y[a].x;
			if (y[a].opt==1) tri[y[a].id].ins();
			if (y[a].opt==2) tri[y[a].id].help();
			if (y[a].opt==3) tri[y[a].id].del();
		}
		if (!able) printf("ERROR\n");
		else printf("%d shades\n",ans);
	}

	return 0;
}
