#include <bits/stdc++.h>
 
FILE *in = fopen("pseudobil.in", "r"), *out = fopen("pseudobil.out", "w") ;
 
const int MV = 3003 ;
 
int mat[MV][MV] ;
 
int main() {
        int p, n, k, d ;
        fscanf(in, "%d %d %d %d", &p, &n, &k, &d) ;
        if (p == 1) {
                fprintf(out, "%d", 2 * ((d - 2) / 2) * ((d - 2) / 2) + d - 1) ;
                return 0 ;
        }
        int x, y, nx, ny ;
        for (int i = 1 ; i <= k ; ++ i) {
                fscanf(in, "%d %d", &x, &y) ;
                mat[n + x - y][x + y - 1] = 1 ;
        }
        for (int i = 1 ; i <= 2 * n ; ++ i) {
                for (int j = 1 ; j <= 2 * n ; ++ j) {
                        mat[i][j] += mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1] ;
                }
        }
        int m ;
        fscanf(in, "%d", &m) ;
        for (int i = 1 ; i <= m ; ++ i) {
                fscanf(in, "%d %d", &x, &y) ;
                nx = n + x - y ;
                ny = x + y - 1 ;
                fprintf(out, "%d\n", mat[nx + d][ny + d] - mat[nx + d][ny - 1] - mat[nx - 1][ny + d] + mat[nx - 1][ny - 1]) ;
        }
}
