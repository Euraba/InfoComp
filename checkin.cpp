#include <cstdio>
#include <algorithm>
#include <vector>
 
const int VM = 1e3 + 5 ;
 
long long A[VM], B[VM], v[VM] ;
long long n, k, p ;
long long step(1LL << 33), pos(0) ;
 
bool verificare(long long temp) {
    long long suma(0), poz(0) ;
    bool ok(0) ;
    register long long i ;
    for (i = 1 ; i <= n ; ++ i) {
        if (B[i] <= temp) {
            v[++ poz] = (temp - B[i]) / A[i] ;
            ok = 1 ;
        }
    }
    std::sort(v + 1, v + 1 + poz) ;
    for (i = std::max(poz - k + 1, 1LL) ; i <= poz ; ++ i)
        suma += v[i] ;
    return (suma >= p && ok) ;
}
 
long long CautBinar() {
    while (step != 0) {
        if (!verificare(step + pos))
            pos += step ;
        step >>= 1 ;
    }
    return pos + 1 ;
}
 
int main(){
    freopen("checkin.in","r",stdin) ;
    freopen("checkin.out","w",stdout) ;
    scanf("%d", &n) ;
    register long long i ;
    for (i = 1 ; i <= n ; ++ i) {
        scanf("%lld %lld", &A[i], &B[i]) ;
    }
    scanf("%lld %lld", &k, &p) ;
    long long answer = CautBinar() ;
    printf("%lld", answer) ;
    return 0;
}
