inline long long Scan()     //输入外挂
{
    long long res=0,ch,flag=0;
    if((ch=getchar())=='-')
        flag=1;
    else if(ch>='0'&&ch<='9')
        res=ch-'0';
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-'0';
    return flag?-res:res;
}
inline void Out(long long a)    //输出外挂
{
    if(a>9)
        Out(a/10);
    putchar(a%10+'0');
}

template<class T>
inline bool read(T &n){
    T x = 0, tmp = 1; char c = getchar();
    while ((c < '0' || c > '9') && c != '-' && c != EOF) c = getchar();
    if (c == EOF) return false;
    if (c == '-') c = getchar(), tmp = -1;
    while (c >= '0' && c <= '9') x *= 10, x += (c - '0'), c = getchar();
    n = x*tmp;
    return true;
}

template <class T>
inline void write(T n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    int len = 0, data[20];
    while (n) {
        data[len++] = n % 10;
        n /= 10;
    }
    if (!len) data[len++] = 0;
    while (len--) putchar(data[len] + 48);
}



///////////////////////////////fread加速!!!!!!!!///////////////
char *ch1, buf1[40*1024000+5];
char *ch, buf[40*1024000+5];

template <class T>
void read(T &x) {
	for (++ch; *ch <= 32; ++ch);
	for (x = 0; '0' <= *ch; ch++)	x = x * 10 + *ch - '0';
}

void out(int x) {
	if (!x)	*(++ch1) = '0';
	else {
		char *ch0 = ch1, *ch = ch1 + 1;
		while (x) {
			*(++ch0) = x % 10 + '0';
			x /= 10;
		}
		ch1 = ch0;
		while (ch <= ch0)	swap(*(ch++), *(ch0--));
	}
	*(++ch1) = '\n';
}

void out(long long x) {
	if (!x)	*(++ch1) = '0';
	else {
		char *ch0 = ch1, *ch = ch1 + 1;
		while (x) {
			*(++ch0) = x % 10 + '0';
			x /= 10;
		}
		ch1 = ch0;
		while (ch <= ch0)	swap(*(ch++), *(ch0--));
	}
	*(++ch1) = '\n';
}
int main(){
	Open();//freopen
	ch = buf - 1;
	ch1 = buf1 - 1;
	fread(buf, 1, 1000 * 35 * 1024, stdin);
	
	
	
	
	// fwrite(buf1, 1, ch1 - buf1 + 1, stdout);//输出，放在main函数的最后一行
}
//----------------------比较规整的版本，注意内存消耗比较大-------------
struct Reader{
    static const int MSIZE = 1000 * 8 * 1024;
    char buf[MSIZE], *pt = buf, *o = buf;
    void init(){
        fread(buf, 1, MSIZE, stdin);
    }
    char getch()
    {
        char ch;
        while((*pt < 'A' || *pt > 'Z') && (*pt < 'a' || *pt > 'z')) pt++;
        ch = *pt;pt++;
        return ch;
    }
    int getint()
    {
        int f = 1, x = 0;
        while(*pt != '-' && !isdigit(*pt)) pt++;
        if(*pt == '-') f = -1, pt++;
        else x = *pt++ - 48;
        while(isdigit(*pt)) x = x * 10 + *pt++ - 48;
        return x * f;
    }
}frd;