#include <iostream>
#include <cstdio>
#include <stack>
#include <time.h>

FILE *in = fopen("turnuri4.in", "r"), *out = fopen("turnuri4.out", "w") ;
FILE *deb = fopen("incercare.out", "w") ;

const int maxn = 1e5 ;
const int maxl = 16 ;
const int LIMIT = 1e6 ;

int v[1 + maxn] ;

namespace RMQ {
    int rmq[1 + 16][1 + maxn] ;
    int LG[1 + maxn] ;
    void startRMQ(int n) {
        int i, j ;
        LG[1] = 0 ;
        rmq[0][1] = v[1] ;
        for (i = 2 ; i <= n ; ++ i) {
            LG[i] = LG[i >> 1] + 1 ;
            rmq[0][i] = v[i] ;
        }
        for (i = 1 ; (1 << i) <= n ; ++ i) {
            for (j = 1 ; j + (1 << i) - 1 <= n ; ++ j) {
                int left = rmq[i - 1][j] ;
                int right = rmq[i - 1][j + (1 << (i - 1))] ;
                rmq[i][j] = std::max(left, right) ;
            }
        }
    }
}

int right[1 + maxn] ;
int left[1 + maxn] ;

void getLeft(int n) {
    std::stack<int> S ;
    int i ;
    try {
        for (i = 1; i <= n; ++i) {
            while (!S.empty() && v[S.top()] <= v[i]) {
                S.pop();
            }
            if (S.empty()) {
                left[i] = 1;
            } else left[i] = S.top() + 1;
            S.push(i);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n' ;
    }
}

void getRight(int n) {
    std::stack<int> S ;
    int i ;
    try {
        for (i = n; i >= 1; --i) {
            while (!S.empty() && v[S.top()] <= v[i]) {
                S.pop();
            }
            if (S.empty()) {
                right[i] = n;
            } else right[i] = S.top() - 1;
            S.push(i);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n' ;
    }
}

int maxim(int l, int r) {
    int dist(r - l + 1) ;
    int size(RMQ::LG[dist]) ;
    int ret = std::max(RMQ::rmq[size][l], RMQ::rmq[size][r - (1 << size) + 1]) ;
    return ret ;
}

int ans[1 + maxn] ;
[[maybe_unused]]int ignore[1 + maxn] ;

void brut(int n) {
    int i, j ;
    int ret ;
    for (i = 1 ; i <= n ; ++ i) {
        ret = 0 ;
        int app = v[i] ;
        v[i] = 0 ;
        getLeft(n) ;
        getRight(n) ;
        for (j = 1 ; j <= n ; ++ j) {
            ret += right[j] - left[j] + 1 ;
        }
        fprintf(deb, "%d ", ret) ;
        if (ret != ignore[i]) {
            throw std::runtime_error("Ai gresit la indicele " + i);
        }

        v[i] = app ;
    }
}

int main() {
    int buildings, i ;
    fscanf(in, "%d", &buildings) ;
    srand(time(NULL)) ;
    for (i = 1 ; i <= buildings ; ++ i) {
#ifdef INFOARENA
        fscanf(in, "%d", v + i) ;
#else
        v[i] = rand() % LIMIT + 1 ;
#endif
    }
    v[buildings + 1] = 1e9 ;
    RMQ::startRMQ(buildings + 1) ;
    getRight(buildings) ;
    getLeft(buildings) ;
    int normal(0) ;
    try {
        for (i = 1; i <= buildings; ++i) {
            int leftInt = left[i];
            int rightInt = right[i];
            normal += (rightInt - leftInt + 1);
#ifndef INFOARENA
            std::cerr << i << " -> " << leftInt << ' ' << rightInt << '\n';
#endif
            int ret(0);
            for (int step(1 << maxl); step; step >>= 1) {
                if ((leftInt - 1) - (ret + step) + 1 > 0 &&
                    maxim((leftInt - 1) - (ret + step) + 1, leftInt - 2) <= v[i]) {
                    ret |= step;
                }
            }
            if (ret == 0) {
                ret = 1;
            }
            ans[leftInt - 1] += ret;
#ifndef INFOARENA
            std::cerr << i << " -> " << leftInt - 1 - ret + 1 << ' ';
#endif
            ret = (0);
            for (int step(1 << maxl); step; step >>= 1) {
                if ((rightInt + 1) + (ret + step) - 1 <= buildings &&
                    maxim(rightInt + 2, (rightInt + 1) + (ret + step) - 1) <= v[i]) {
                    ret |= step;
                }
            }
            if (ret == 0) {
                ret = 1;
            }
#ifndef INFOARENA
            std::cerr << rightInt + 1 + ret - 1 << '\n';
#endif
            ans[rightInt + 1] += ret;
        }
    } catch (std::exception& e) {
        std::cerr << e.what() ;
    }
    std::cerr << normal << '\n' ;
    for (i = 1 ; i <= buildings ; ++ i) {
#ifndef INFOARENA
        ignore[i] = normal + ans[i] - (right[i] - left[i] + 1) + 1 ;
        fprintf(out, "%d ", ignore[i]) ;
#else
        fprintf(out, "%d\n", normal + ans[i] - (right[i] - left[i] + 1) + 1) ;
#endif
    }
#ifndef INFOARENA
    fputc('\n', out) ;
    brut(buildings) ;
#endif
}
