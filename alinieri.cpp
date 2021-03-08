#include <iostream>
#include <cstdio>
 
#ifndef InputReader_H
#define InputReader_H
 
#include <cstdio>
 
template <typename T>
class InputReader {
private:
    FILE *input_file ;
    static const int SIZE = (1 << 17) ;
    int point ;
    char buffer[SIZE] ;
    __attribute__ ( (always_inline)) void advance() {
        ++ point ;
        if (point == SIZE) {
            point = 0 ;
            fread (buffer, SIZE, 1, input_file) ;
        }
    }
public:
    InputReader() {}
    InputReader (const char *file_name) {
        input_file = fopen (file_name, "r") ;
        point = 0 ;
        fread (buffer, SIZE, 1, input_file) ;
    }
    __attribute__ ( (always_inline)) InputReader &operator >> (T &n) {
        for (; !isdigit (buffer[point]) ; advance()) ;
        n = 0 ;
        for (; isdigit (buffer[point]) ; advance()) {
            n = n * 10 + buffer[point] - '0' ;
        }
        return *this ;
    }
} ;
 
#endif //UNTITLED1_LIBRARY_H
 
InputReader<int> in("alinieri.in") ;
auto *out = fopen("alinieri.out", "w") ;
 
 
const int maxv = 180 ;
 
int ap[1 + maxv] ;
int upd[1 + maxv] ;
 
int main() {
    int n, p, z, i, j, x ;
    in >> n >> p >> z ;
    for (i = 1 ; i <= n ; ++ i) {
        in >> x ;
        ap[x % 180] ++ ;
    }
    int days, deg, zz(z % 180) ;
    int ret(0), rest(0), r(0) ;
    for (days = 1 ; days <= 180 ; ++ days) {
        r = 0 ;
        for (deg = 0 ; deg < 180 ; ++ deg) {
            upd[r] += ap[deg] ;
            r += days ;
            if (r >= 180) {
                r -= 180 ;
            }
        }
        int add(0) ;
        for (deg = 0 ; deg < 180 ; ++ deg) {
            add += upd[deg] >= p ;
            upd[deg] = 0 ;
        }
        rest += add * (days <= zz) ;
        ret += add ;
    }
    int final = ret * (z / 180) + rest ;
    fprintf(out, "%d", final) ;
}
