#include <bits/stdc++.h>
 
FILE *in = fopen("deminare.in", "r"), *out = fopen("deminare.out", "w") ;
 
const int MV = 501 ;
 
int v[MV] ;
int dp[MV][MV] ;
int task, ll, cc, mines ;
 
void Do_SubTask_one() {
  int i, maxx(-1) ;
  for (i = 1 ; i <= ll ; ++ i) { maxx = std::max(maxx, v[i]) ; }
  for (i = 1 ; i <= ll ; ++ i) { if (v[i] == maxx) {
      fprintf(out, "%d ", i) ; } } }
 
int main() {
  int x, y ;
  fscanf(in, "%d\n%d %d\n%d", &task, &ll, &cc, &mines) ;
  int area = mines ;
  while (mines --) { fscanf(in, "%d %d\n", &x, &y) ;
    v[x] ++ ; dp[x][y] ++ ; }
  if (task == 1) {
    return Do_SubTask_one(), 0 ; }
  int i, j ;
  for (i = 1 ; i <= ll ; ++ i) { for (j = 1 ; j <= cc ; ++ j) {
      dp[i][j] = dp[i][j] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] ; } }
  int l, c, k = 1, ans(1e9) ;
  for (; k * k <= area ; ++ k) {
    if (area % k == 0) {
      l = k ; c = area / k ;
      if (l <= ll && c <= cc) { for (i = l ; i <= ll ; ++ i) { for (j = c ; j <= cc ; ++ j) {
        ans = std::min(ans, area - (dp[i][j] - dp[i - l][j] - dp[i][j - c] + dp[i - l][j - c])) ; } } }
      l = area / k ; c = k ;
      if (l <= ll && c <= cc) { for (i = l ; i <= ll ; ++ i) { for (j = c ; j <= cc ; ++ j) {
        ans = std::min(ans, area - (dp[i][j] - dp[i - l][j] - dp[i][j - c] + dp[i - l][j - c])) ; } } } } }
  if (ans == 1e9) {
    fprintf(out, "-1") ;
    return 0 ; }
  fprintf(out, "%d", ans) ; }
