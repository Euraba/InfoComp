#include <bits/stdc++.h>
 
FILE *in = fopen("unuzero.in", "r"), *out = fopen("unuzero.out", "w") ;
 
const int MOD = 666013 ;
const int MV = 2e6 ;
 
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
 
int dp1[MV + 1] ; /// dp1[i] = cate siruti valide de lungime i care se termina in 1 exista
int dp0[MV + 1] ; /// dp0[i] = cate siruti valide de lungime i care se termina in 0 exista
int psm[MV + 1] ; /// pentru recurenta de la dp1 in O(1)
 
/// Si-au batut joc dinamica la a 9-a
 
void fix(int &x) {
  if (x < 0) {
    x += MOD ;
  }
  if (x >= MOD) {
    x -= MOD ;
  }
  if (x >= MOD) {
    x %= MOD ;
  }
}
 
int main() {
  int n, p, q ;
  register int i ;
  fscanf(in, "%d %d %d", &n, &p, &q) ;
  dp0[0] = psm[0] = 1 ;
  for (i = 1 ; i <= n ; ++ i) {
    dp0[i] = dp0[i - 1] + dp1[i - 1] ; /// punem 0 pe pozitia i
    fix(dp0[i]) ;
    if (i >= p) {
      if (i >= q + 1) {
        dp1[i] = psm[i - p] - psm[i - q - 1] ; /// punem 1 pe pozitii intermadiare
        fix(dp1[i]) ;
      } else {
        dp1[i] = psm[i - p] ;
        fix(dp1[i]) ;
      }
    }
    psm[i] = psm[i - 1] + dp0[i] ;
    fix(psm[i]) ;
  }
  int ans = dp1[n] + dp0[n] - 1 ;
  fix(ans) ;
  fprintf(out, "%d", ans) ;
}
