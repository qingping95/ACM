const int MAXN = 100005 ;  
const int N = 26 ;  
  
struct Palindromic_Tree {  
    int next[MAXN][N] ;//nextָ�룬nextָ����ֵ������ƣ�ָ��Ĵ�Ϊ��ǰ�����˼���ͬһ���ַ�����  
    int fail[MAXN] ;//failָ�룬ʧ�����ת��failָ��ָ��Ľڵ�  
    int cnt[MAXN] ;  
    int num[MAXN] ;  
    int len[MAXN] ;//len[i]��ʾ�ڵ�i��ʾ�Ļ��Ĵ��ĳ���  
    int S[MAXN] ;//�����ӵ��ַ�  
    int last ;//ָ����һ���ַ����ڵĽڵ㣬������һ��add  
    int n ;//�ַ�����ָ��  
    int p ;//�ڵ�ָ��  
  
    int newnode ( int l ) {//�½��ڵ�  
        for ( int i = 0 ; i < N ; ++ i ) next[p][i] = 0 ;  
        cnt[p] = 0 ;  
        num[p] = 0 ;  
        len[p] = l ;  
        return p ++ ;  
    }  
  
    void init () {//��ʼ��  
        p = 0 ;  
        newnode (  0 ) ;  
        newnode ( -1 ) ;  
        last = 0 ;  
        n = 0 ;  
        S[n] = -1 ;//��ͷ��һ���ַ�����û�е��ַ�����������  
        fail[0] = 1 ;  
    }  
  
    int get_fail ( int x ) {//��KMPһ����ʧ�����һ���������  
        while ( S[n - len[x] - 1] != S[n] ) x = fail[x] ;  
        return x ;  
    }  
  
    void add ( int c ) {  
        c -= 'a' ;  
        S[++ n] = c ;  
        int cur = get_fail ( last ) ;//ͨ����һ�����Ĵ���������Ĵ���ƥ��λ��  
        if ( !next[cur][c] ) {//���������Ĵ�û�г��ֹ���˵��������һ���µı��ʲ�ͬ�Ļ��Ĵ�  
            int now = newnode ( len[cur] + 2 ) ;//�½��ڵ�  
            fail[now] = next[get_fail ( fail[cur] )][c] ;//��AC�Զ���һ������failָ�룬�Ա�ʧ�����ת  
            next[cur][c] = now ;  
            num[now] = num[fail[now]] + 1 ;  
        }  
        last = next[cur][c] ;  
        cnt[last] ++ ;  
    }  
  
    void count () {  
        for ( int i = p - 1 ; i >= 0 ; -- i ) cnt[fail[i]] += cnt[i] ;  
        //�����ۼӶ��ӵ�cnt����Ϊ���fail[v]=u����uһ����v���ӻ��Ĵ���  
    }  
} ;  