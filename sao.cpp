#include <stdio.h>
#include <queue>
std::priority_queue<long long> pq ;
int main(void){
    freopen("sao.in","r",stdin) ;
    freopen("sao.out","w",stdout) ;
    long long n ,k ,hp ,a ,i ;
    scanf("%lld%lld%lld" ,&n ,&k ,&hp) ;
    for (i = 1 ; i <= n ; ++ i){
        scanf("%lld",&a) ,pq.push(a) ;
        hp -= a ;
        while (not pq.empty() and k and hp <= 0 )
            k -- ,hp += pq.top() ,pq.pop() ;
        if (hp < 0){
            printf("%lld" ,--i) ;
            return 0 ;
        }
        if (hp == 0){
            printf("%lld",i) ;
            return 0 ;
        }
    }
    printf("%lld",n) ;
    return 0;
}
