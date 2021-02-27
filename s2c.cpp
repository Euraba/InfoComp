#include <bits/stdc++.h>
 
FILE *in = fopen("s2c.in", "r"), *out = fopen("s2c.out", "w") ;
 
const int INF = 1000000  ;
const int MV = 2000  ;
const int MN = 30000  ;
 
int c[MN + 1], v[MV + 1], norm[MN + 1], dp[MV + 1][MV + 1], last[MV + 1], maxuntil[MV + 1][MV + 1] ;
 
void solve() {
  int n, i, j, k, ans ;
  fscanf(in, "%d", &n) ;
  for (i = 1 ; i <= n ; ++ i) {
    fscanf(in, "%d", v + i) ;
    c[v[i]] = 1 ; }
  k = 0 ;
  for (i = 1 ; i <= MN ; ++ i) {
    if (c[i] == 1) {
      c[i] = 0 ;
      norm[i] = ++ k ;
      last[k] = n ; } }
  ans = 0 ;
  for (i = 1 ; i <= n ; ++ i) {
    maxuntil[i][0] = -INF ;
    for (j = 1 ; j <= k ; ++ j) {
      if (last[j] < i) {
        if (2 < 1 + maxuntil[last[j]][norm[v[i]] - 1]) { dp[i][j] = 1 + maxuntil[last[j]][norm[v[i]] - 1] ; }
        else { dp[i][j] = 2 ; } }
      else { dp[i][j] = -INF ; }
      if (maxuntil[i][j - 1] < dp[i][j]) { maxuntil[i][j] = dp[i][j] ; }
      else { maxuntil[i][j] = maxuntil[i][j - 1] ; } }
    if (ans < maxuntil[i][k]) { ans = maxuntil[i][k] ; }
    last[norm[v[i]]] = i ; }
  fprintf(out, "%d\n", ans) ; }
 
int main() {
  int t ;
  fscanf(in, "%d", &t) ;
  for (; t ; t--) {
    solve() ; }
  return 0 ; }
