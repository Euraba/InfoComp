#include <bits/stdc++.h>
 
const int MV = 5005 ;
const int MD = 20 ;
 
const long def[20] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 39, 41, 43, 47, 51, 53, 57 } ;
long long mod = 1000000007 ;
 
long querys, v, e, cont, x, y, root ;
long dp[MV][MD] ;
bool vis[MV] ;
std::vector<long> lista[MV] ;
long long ans ;
 
void renewConfig() {
  cont = 0 ;
  memset(dp, 0, sizeof(dp)) ;
  memset(vis, 0, sizeof(vis)) ;
  for (long i = 1 ; i <= v ; ++ i)
    lista[i].clear() ; }
 
void dfs(long nod) {
  long i, j, newCont = 0, pos ;
  vis[nod] = true ;
  if (lista[nod].size() == 0) return ;
  for (i = 0 ; i < lista[nod].size() ; ++ i) {
    long newNod = lista[nod][i] ;
    if (!vis[newNod]) {
      dfs(newNod) ; }
    for (j = 1 ; j <= cont ; j++) {
     dp[nod][j] = std::max(dp[nod][j], dp[newNod][j]) ; } }
  for (i = 1 ; i <= cont ; ++ i) {
    if (dp[nod][i]) {
      newCont ++, pos = i ; } }
  if (newCont == 0) {
    dp[nod][++cont] = 1 ; }
  else if (newCont == 1) {
    dp[nod][pos]++ ; }
}
 
long long poww(long long a, long long b) {
  long long ans = 1 ;
  while (b) {
    if (b & 1) {
      ans = (ans * a) % mod ; }
    a = (a * a) % mod ;
    b >>= 1 ; }
  return ans ; }
 
int main() {
  freopen("divisorgraph.in", "r", stdin) ;
  freopen("divisorgraph.out", "w", stdout) ;
  long i ;
  scanf("%ld", &querys) ;
  while (querys --) {
    renewConfig() ;
    scanf("%ld %ld", &v, &e) ;
    for (i = 1 ; i <= e ; ++ i) {
      scanf("%ld %ld", &x, &y) ;
      lista[x].push_back(y) ;
      if (lista[x].size() == v - 1) {
        root = x ; } }
    dfs(root) ;
    std::sort(dp[root] + 1, dp[root] + cont + 1) ; ans = 1 ;
    for (i = 1 ; i <= cont ; ++ i) {
      if (!dp[root][i]) {
        continue ; }
      ans = (long long)(ans * poww(def[cont - i + 1], dp[root][i])) % mod ; }
    printf("%lld\n", ans) ; }
  return 0 ; }
