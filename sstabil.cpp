#include <bits/stdc++.h>
 
FILE *in = fopen("sstabil.in", "r"), *out = fopen("sstabil.out", "w") ;
 
const int MV = 1e6 ;
 
int num[MV + 1] ;
int sol[MV + 1] ;
int k ;
 
void solve(int n) {
  int idx(n) ;
  int suma(0) ;
  while (idx > 0 && suma < 10) {
    suma += num[idx] ;
    idx -- ;
  }
  if (suma < 10) {
    sol[++ k] = suma ;
    return ;
  }
  idx = n ;
  int curr = num[idx] ;
  while (suma - curr >= 10 || sol[k] + curr < 10) {
    idx -- ;
    curr += num[idx] ;
  }
  sol[++ k] = curr ;
  solve(idx - 1) ;
}
 
int main() {
  int n ; fscanf(in, "%d", &n) ;
  register int i ; sol[0] = 10 ;
  for (i = 1 ; i <= n ; ++ i) {
    fscanf(in, "%d", num + i) ;
  }
  solve(n) ;
  for (i = k ; i >= 1 ; -- i) {
    fprintf(out, "%d", sol[i]) ;
  }
}
