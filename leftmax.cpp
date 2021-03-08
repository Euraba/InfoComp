#include <iostream>
#include <cstdio>
#include <stack>
 
auto *in = fopen("leftmax.in", "r") ;
auto *out = fopen("leftmax.out", "w") ;
 
const int maxn = 1e5 ;
const int MOD = 1e9 + 7 ;
 
int v[1 + maxn] ;
int left[1 + maxn], right[1 + maxn] ;
int n ;
 
using i64 = long long ;
 
void Left() {
    std::stack<int> ss ;
    ss.push(0) ;
    int i ;
    for (i = 1 ; i <= n ; ++ i) {
        while (!ss.empty() && v[ss.top()] < v[i]) {
            ss.pop() ;
        }
        left[i] = ss.top() + 1 ;
        ss.push(i) ;
    }
}
 
void Right() {
    std::stack<int> ss ;
    ss.push(n + 1) ;
    int i ;
    for (i = n ; i >= 1 ; -- i) {
        while (!ss.empty() && v[ss.top()] < v[i]) {
            ss.pop() ;
        }
        right[i] = ss.top() - 1 ;
        ss.push(i) ;
    }
}
 
i64 sum(int x) {
    i64 a = 1ll * x * (x + 1) / 2 ;
    return a ;
}
 
int main() {
    int i ;
    fscanf(in, "%d ", &n) ;
    for (i = 1 ; i <= n ; ++ i) {
        fscanf(in, "%d", v + i) ;
    }
    v[0] = v[n + 1] = 1e9 ;
    Left() ;
    Right() ;
    i64 ret(0) ;
    for (i = 1 ; i <= n ; ++ i) {
        int distleft = i - left[i] ;
        int distright = right[i] - i ;
        if (distright <= distleft) {
            ret += sum(distright + 1) ;
        } else {
            ret += sum(distleft + 1) + (distright - distleft) * (distleft + 1) ;
        }
        ret %= MOD ;
    }
    fprintf(out, "%d", ret) ;
}
