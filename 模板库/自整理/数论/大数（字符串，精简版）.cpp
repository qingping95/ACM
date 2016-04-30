#include <cstdio>
#include <cstring>
#include <cstdlib>
//��������1120λ�������ƣ����м���
#define BI_MAXLEN 105
#define DEC 10
#define HEX 16

class CBigInt
{
public:
//������0x100000000�����µĳ���
    unsigned m_nLength;
//�������¼������0x100000000������ÿһλ��ֵ
    unsigned long m_ulValue[BI_MAXLEN];

    CBigInt();
    ~CBigInt();

/*****************************************************************
��������������
Mov����ֵ���㣬�ɸ�ֵΪ��������ͨ������������Ϊ�������=��
Cmp���Ƚ����㣬������Ϊ�������==������!=������>=������<=����
Add���ӣ��������������������ͨ�����ĺͣ�������Ϊ�������+��
Sub�������������������������ͨ�����Ĳ������Ϊ�������-��
Mul���ˣ��������������������ͨ�����Ļ���������Ϊ�������*��
Div�������������������������ͨ�������̣�������Ϊ�������/��
Mod��ģ���������������������ͨ������ģ��������Ϊ�������%��
*****************************************************************/
    void Mov(unsigned __int64 A);
    void Mov(CBigInt A);
    CBigInt Add(CBigInt& A);
    CBigInt Sub(CBigInt A);
    CBigInt Mul(CBigInt& A);
    CBigInt Div(CBigInt& A);
    CBigInt Mod(CBigInt& A);
    CBigInt Add(unsigned long A);
    CBigInt Sub(unsigned long A);
    CBigInt Mul(unsigned long A);
    CBigInt Div(unsigned long A);
    unsigned long Mod(unsigned long A);
    int Cmp(CBigInt& A);

/*****************************************************************
�������
Get�����ַ�����10���ƻ�16���Ƹ�ʽ���뵽����
Put����������10���ƻ�16���Ƹ�ʽ������ַ���
*****************************************************************/
    void Get(char str[], unsigned int system=DEC);
    void Put(char str[], unsigned int system=DEC);

};
//����������󲢳�ʼ��Ϊ��
CBigInt::CBigInt()
{
    m_nLength=1;
    for(int i=0;i<BI_MAXLEN;i++)m_ulValue[i]=0;
}

//�⹹��������
CBigInt::~CBigInt()
{
}

/****************************************************************************************
�����Ƚ�
���÷�ʽ��N.Cmp(A)
����ֵ����N<A����-1����N=A����0����N>A����1
****************************************************************************************/
int CBigInt::Cmp(CBigInt& A)
{
    if(m_nLength>A.m_nLength)return 1;
    if(m_nLength<A.m_nLength)return -1;
    for(int i=m_nLength-1;i>=0;i--)
    {
        if(m_ulValue[i]>A.m_ulValue[i])return 1;
        if(m_ulValue[i]<A.m_ulValue[i])return -1;
    }
    return 0;
}

/****************************************************************************************
������ֵ
���÷�ʽ��N.Mov(A)
����ֵ���ޣ�N����ֵΪA
****************************************************************************************/
void CBigInt::Mov(CBigInt A)
{
    m_nLength=A.m_nLength;
    for(int i=0;i<BI_MAXLEN;i++)m_ulValue[i]=A.m_ulValue[i];
}

void CBigInt::Mov(unsigned __int64 A)
{
    if(A>0xffffffff)
    {
        m_nLength=2;
        m_ulValue[1]=(unsigned long)(A>>32);
        m_ulValue[0]=(unsigned long)A;
    }
    else
    {
        m_nLength=1;
        m_ulValue[0]=(unsigned long)A;
    }
    for(int i=m_nLength;i<BI_MAXLEN;i++)m_ulValue[i]=0;
}

/****************************************************************************************
�������
������ʽ��N.Add(A)
����ֵ��N+A
****************************************************************************************/
CBigInt CBigInt::Add(CBigInt& A)
{
    CBigInt X;
    X.Mov(*this);
    unsigned carry=0;
    unsigned __int64 sum=0;
    if(X.m_nLength<A.m_nLength)X.m_nLength=A.m_nLength;
    for(unsigned i=0;i<X.m_nLength;i++)
    {
        sum=A.m_ulValue[i];
		sum=sum+X.m_ulValue[i]+carry;
        X.m_ulValue[i]=(unsigned long)sum;
        carry=(unsigned)(sum>>32);
    }
    X.m_ulValue[X.m_nLength]=carry;
    X.m_nLength+=carry;
    return X;
}

CBigInt CBigInt::Add(unsigned long A)
{
    CBigInt X;
    X.Mov(*this);
    unsigned __int64 sum;
    sum=X.m_ulValue[0];
	sum+=A;
    X.m_ulValue[0]=(unsigned long)sum;
    if(sum>0xffffffff)
    {
        unsigned i=1;
        while(X.m_ulValue[i]==0xffffffff){X.m_ulValue[i]=0;i++;}
        X.m_ulValue[i]++;
        if(m_nLength==i)m_nLength++;
    }
    return X;
}

/****************************************************************************************
�������
������ʽ��N.Sub(A)
����ֵ��N-A
****************************************************************************************/
CBigInt CBigInt::Sub(CBigInt A)
{
    CBigInt X;
    X.Mov(*this);
    if(X.Cmp(A)<=0){X.Mov(0);return X;}
    unsigned carry=0;
    unsigned __int64 num;
	unsigned i;
    for(i=0;i<m_nLength;i++)
    {
        if((m_ulValue[i]>A.m_ulValue[i])||((m_ulValue[i]==A.m_ulValue[i])&&(carry==0)))
        {
            X.m_ulValue[i]=m_ulValue[i]-carry-A.m_ulValue[i];
            carry=0;
        }
        else
        {
            num=0x100000000+m_ulValue[i];
            X.m_ulValue[i]=(unsigned long)(num-carry-A.m_ulValue[i]);
            carry=1;
        }
    }
    while(X.m_ulValue[X.m_nLength-1]==0)X.m_nLength--;
    return X;
}

CBigInt CBigInt::Sub(unsigned long A)
{
    CBigInt X;
    X.Mov(*this);
    if(X.m_ulValue[0]>=A){X.m_ulValue[0]-=A;return X;}
    if(X.m_nLength==1){X.Mov(0);return X;}
    unsigned __int64 num=0x100000000+X.m_ulValue[0];
    X.m_ulValue[0]=(unsigned long)(num-A);
    int i=1;
    while(X.m_ulValue[i]==0){X.m_ulValue[i]=0xffffffff;i++;}
    X.m_ulValue[i]--;
    if(X.m_ulValue[i]==0)X.m_nLength--;
    return X;
}

/****************************************************************************************
�������
������ʽ��N.Mul(A)
����ֵ��N*A
****************************************************************************************/
CBigInt CBigInt::Mul(CBigInt& A)
{
    if(A.m_nLength==1)return Mul(A.m_ulValue[0]);
	CBigInt X;
	unsigned __int64 sum,mul=0,carry=0;
	unsigned i,j;
	X.m_nLength=m_nLength+A.m_nLength-1;
    for(i=0;i<X.m_nLength;i++)
	{
		sum=carry;
		carry=0;
		for(j=0;j<A.m_nLength;j++)
		{
            if(((i-j)>=0)&&((i-j)<m_nLength))
			{
				mul=m_ulValue[i-j];
				mul*=A.m_ulValue[j];
			    carry+=mul>>32;
				mul=mul&0xffffffff;
				sum+=mul;
			}
        }
		carry+=sum>>32;
		X.m_ulValue[i]=(unsigned long)sum;
	}
	if(carry){X.m_nLength++;X.m_ulValue[X.m_nLength-1]=(unsigned long)carry;}
    return X;
}

CBigInt CBigInt::Mul(unsigned long A)
{
    CBigInt X;
    unsigned __int64 mul;
    unsigned long carry=0;
    X.Mov(*this);
    for(unsigned i=0;i<m_nLength;i++)
    {
        mul=m_ulValue[i];
        mul=mul*A+carry;
        X.m_ulValue[i]=(unsigned long)mul;
        carry=(unsigned long)(mul>>32);
    }
    if(carry){X.m_nLength++;X.m_ulValue[X.m_nLength-1]=carry;}
    return X;
}

/****************************************************************************************
�������
������ʽ��N.Div(A)
����ֵ��N/A
****************************************************************************************/
CBigInt CBigInt::Div(CBigInt& A)
{
    if(A.m_nLength==1)return Div(A.m_ulValue[0]);
    CBigInt X,Y,Z;
    unsigned i,len;
    unsigned __int64 num,div;
    Y.Mov(*this);
    while(Y.Cmp(A)>=0)
    {
		div=Y.m_ulValue[Y.m_nLength-1];
		num=A.m_ulValue[A.m_nLength-1];
		len=Y.m_nLength-A.m_nLength;
		if((div==num)&&(len==0)){X.Mov(X.Add(1));break;}
		if((div<=num)&&len){len--;div=(div<<32)+Y.m_ulValue[Y.m_nLength-2];}
		div=div/(num+1);
		Z.Mov(div);
		if(len)
		{
			Z.m_nLength+=len;
			for(i=Z.m_nLength-1;i>=len;i--)Z.m_ulValue[i]=Z.m_ulValue[i-len];
			for(i=0;i<len;i++)Z.m_ulValue[i]=0;
		}
		X.Mov(X.Add(Z));
        Y.Mov(Y.Sub(A.Mul(Z)));
    }
    return X;
}

CBigInt CBigInt::Div(unsigned long A)
{
    CBigInt X;
    X.Mov(*this);
    if(X.m_nLength==1){X.m_ulValue[0]=X.m_ulValue[0]/A;return X;}
    unsigned __int64 div,mul;
    unsigned long carry=0;
    for(int i=X.m_nLength-1;i>=0;i--)
    {
        div=carry;
        div=(div<<32)+X.m_ulValue[i];
        X.m_ulValue[i]=(unsigned long)(div/A);
        mul=(div/A)*A;
        carry=(unsigned long)(div-mul);
    }
    if(X.m_ulValue[X.m_nLength-1]==0)X.m_nLength--;
    return X;
}

/****************************************************************************************
������ģ
������ʽ��N.Mod(A)
����ֵ��N%A
****************************************************************************************/
CBigInt CBigInt::Mod(CBigInt& A)
{
    CBigInt X,Y;
	unsigned __int64 div,num;
    unsigned long carry=0;
	unsigned i,len;
    X.Mov(*this);
    while(X.Cmp(A)>=0)
    {
		div=X.m_ulValue[X.m_nLength-1];
		num=A.m_ulValue[A.m_nLength-1];
		len=X.m_nLength-A.m_nLength;
		if((div==num)&&(len==0)){X.Mov(X.Sub(A));break;}
		if((div<=num)&&len){len--;div=(div<<32)+X.m_ulValue[X.m_nLength-2];}
		div=div/(num+1);
		Y.Mov(div);
		Y.Mov(A.Mul(Y));
		if(len)
		{
			Y.m_nLength+=len;
			for(i=Y.m_nLength-1;i>=len;i--)Y.m_ulValue[i]=Y.m_ulValue[i-len];
			for(i=0;i<len;i++)Y.m_ulValue[i]=0;
		}
        X.Mov(X.Sub(Y));
    }
    return X;
}

unsigned long CBigInt::Mod(unsigned long A)
{
    if(m_nLength==1)return(m_ulValue[0]%A);
    unsigned __int64 div;
    unsigned long carry=0;
    for(int i=m_nLength-1;i>=0;i--)
    {
        div=m_ulValue[i];
		div+=carry*0x100000000;
        carry=(unsigned long)(div%A);
    }
    return carry;
}

/****************************************************************************************
���ַ�����10���ƻ�16���Ƹ�ʽ���뵽����
���ø�ʽ��N.Get(str,sys)
����ֵ��N����ֵΪ��Ӧ����
sys��ʱֻ��Ϊ10��16
****************************************************************************************/
void CBigInt::Get(char str[], unsigned int system)
{
    int len=strlen(str),k;
    Mov(0);
    for(int i=0;i<len;i++)
    {
       Mov(Mul(system));
       if((str[i]>='0')&&(str[i]<='9'))k=str[i]-48;
       else if((str[i]>='A')&&(str[i]<='F'))k=str[i]-55;
       else if((str[i]>='a')&&(str[i]<='f'))k=str[i]-87;
       else k=0;
       Mov(Add(k));
    }
}

/****************************************************************************************
��������10���ƻ�16���Ƹ�ʽ���Ϊ�ַ���
���ø�ʽ��N.Put(str,sys)
����ֵ���ޣ�����str����ֵΪN��sys�����ַ���
sys��ʱֻ��Ϊ10��16
****************************************************************************************/
void CBigInt::Put(char str[], unsigned int system)
{
    if((m_nLength==1)&&(m_ulValue[0]==0)){str="0";return;}
    char t[]="0123456789ABCDEF";
    int a;
    char ch;
    CBigInt X;
    X.Mov(*this);
	int i = 0;
    while(X.m_ulValue[X.m_nLength-1]>0)
    {
        a=X.Mod(system);
        ch=t[a];
        str[i++] = ch;
        X.Mov(X.Div(system));
    }
	str[i] = 0x00;

	int len = strlen(str) - 1;
	int half_len = strlen(str) / 2;
	char tmp;
	for (i = 0; i<half_len; i++)
	{
		tmp = str[i];
		str[i] = str[len-i];
		str[len-i] = tmp;
	}
}


int main()
{
	int t;
	int i, j;
	CBigInt big_a, big_b, big_ans;
	char ans[2005], a[1005], b[1005];
	while (scanf("%d", &t) != EOF)
	{
		for (i = 0; i<t; i++)
		{
			if (i != 0)
				printf("\n");
			scanf("%s%s", a, b);
			big_a.Get(a);
			big_b.Get(b);
			big_a.Put(a);
			big_b.Put(b);
			big_ans = big_a.Add(big_b);
			big_ans.Put(ans);
			printf("Case %d:\n%s + %s = %s\n", i+1, a, b, ans);
		}
	}
	return 0;
}
