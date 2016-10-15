#include <cstdio>  
#include <cstring>  
#include <algorithm>  
using namespace std ;  
  
const int maxN = 50005 ;  
const int maxW = 256 ;  
const int maxQ = 1000000 ;  
  
struct Trie {  
    int next[ maxN ][ maxW ] ;  
    int fail[ maxN ] ;  
    int end[ maxN ] ;  
    int P , root ;  
    int head , tail ;  
    int Q[ maxN ] ;  
    int hash[ maxW << 1 | 1 ] ;  
      
    int New () {  
        for ( int i = 0 ; i < maxW ; ++ i )  
            next[ P ][ i ] = -1 ;  
        end[ P ] = -1 ;  
        return P ++ ;  
    }  
      
    void Init () {  
        P = 0 ;  
        root = New () ;  
    }  
      
    void Insert ( unsigned char s[] , int len , int id ) {  
        int now = root ;  
        for ( int i = 0 ; i < len ; ++ i ) {  
            int idx = s[ i ] ;  
            if ( next[ now ][ idx ] == -1 ) next[ now ][ idx ] = New () ;  
            now = next[ now ][ idx ] ;  
        }  
        end[ now ] = id ;  
    }  
      
    void Build () {  
        head = tail = 0 ;  
        fail[ root ] = root ;  
        for ( int i = 0 ; i < maxW ; ++ i ) {  
            if ( next[ root ][ i ] == -1 ) {  
                next[ root ][ i ] = root ;  
            }  
            else {  
                fail[ next[ root ][ i ] ] = root ;  
                Q[ tail ++ ] = next[ root ][ i ] ;  
            }  
        }  
        while ( head != tail ) {  
            int now = Q[ head ++ ] ;  
            for ( int i = 0 ; i < maxW ; ++ i ) {  
                if ( next[ now ][ i ] == -1 ) {  
                    next[ now ][ i ] = next[ fail[ now ] ][ i ] ;  
                }  
                else {  
                    fail[ next[ now ][ i ] ] = next[ fail[ now ] ][ i ] ;  
                    Q[ tail ++ ] = next[ now ][ i ] ;  
                }  
            }  
        }  
    }  
      
    int Query ( unsigned char s[]  , int len , int n ) {  
        int now = root , res = 0 ;  
        memset ( hash , 0 , sizeof hash ) ;  
        for ( int i = 0 ; i < len ; ++ i ) {  
            now = next[ now ][ s[i] ] ;  
            int tmp = now ;  
            while ( tmp != root ) {  
                if ( ~end[ tmp ] ) hash[ end[ tmp ] ] = 1 ;  
                tmp = fail[ tmp ] ;  
            }  
        }  
        for ( int i = 0 ; i < n ; ++ i ) if ( hash[ i ] ) ++ res ;  
        return res ;  
    }  
} ;  
  
Trie AC ;  
unsigned char str[ maxN ] ;  
char s[ maxN ] ;  
unsigned char ss[ maxN ] ;  
  
unsigned char Get ( char x ) {  
    if ( x >= 'A' && x <= 'Z' ) return x - 'A'  + 0 ;  
    if ( x >= 'a' && x <= 'z' ) return x - 'a' + 26 ;  
    if ( x >= '0' && x <= '9' ) return x - '0' + 52 ;  
    if ( x == '+' ) return 62 ;  
    return 63 ;  
}  
  
int Encode ( unsigned char s[] , int len ) {  
    int num = 0 ;  
    for ( int i = 0 ; i < len ; i += 4 ) {  
        str[ num ++ ] = ( s[ i ] << 2 ) | ( s[ i + 1 ] >> 4 ) ;  
        if ( i + 2 < len ) str[ num ++ ] = ( s[ i + 1 ] << 4 ) | ( s[ i + 2 ] >> 2 ) ;  
        if ( i + 3 < len ) str[ num ++ ] = ( s[ i + 2 ] << 6 ) | s[ i + 3 ] ;  
    }  
    return num ;  
}  
  
void work () {  
    int n , m ;  
    while ( ~scanf ( "%d" , &n ) ) {  
        AC.Init () ;  
        for ( int i = 0 ; i < n ; ++ i ) {  
            scanf ( "%s" , s ) ;  
            int len = strlen ( s ) ;  
            while ( s[ len - 1 ] == '=' ) -- len ;  
            for ( int j = 0 ; j < len ; ++ j ) ss[ j ] = Get ( s[ j ] ) ;  
            int num = Encode ( ss , len ) ;  
            AC.Insert ( str , num , i ) ;  
        }  
        AC.Build () ;  
        scanf ( "%d" , &m ) ;  
        for ( int i = 0 ; i < m ; ++ i ) {  
            scanf ( "%s" , s ) ;  
            int len = strlen ( s ) ;  
            while ( s[ len - 1 ] == '=' ) -- len ;  
            for ( int j = 0 ; j < len ; ++ j ) ss[ j ] = Get ( s[ j ] ) ;  
            int num = Encode ( ss , len ) ;  
            printf ( "%d\n" , AC.Query ( str , num , n ) ) ;  
        }  
        printf ( "\n" ) ;  
    }  
}  
  
int main () {  
    work () ;  
    return 0 ;  
}  