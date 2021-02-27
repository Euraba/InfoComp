#include <bits/stdc++.h>
 
const int MV = 1e5 ;
const int BAZA = 10 ;
 
std::ifstream in ("puzzle3.in") ;
std::ofstream out ("puzzle3.out") ;
 
int transport[MV + 50] ;
 
inline void solve_test() {
  std::string fi, se, ans ;
  in >> fi >> se >> ans ;
  int len_fi = fi.size() ;
  int len_se = se.size() ;
  int len_ans = ans.size(), i ;
  memset(transport, 0, sizeof transport) ;
  for (i = 0 ; i <= len_ans + 1 ; ++ i) {
    if (i < len_fi) {
      transport[i] += (fi[len_fi - i - 1] == '*') ? BAZA - 1 : fi[len_fi - i - 1] - '0' ; }
    if (i < len_se) {
      transport[i] += (se[len_se - i - 1] == '*') ? BAZA - 1 : se[len_se - i - 1] - '0' ; ///presupun ca fiecare * inseamna trecere peste ordin
    }
    if (i < len_ans) {
      transport[i] -= (ans[len_ans - i - 1] == '*') ? (i == len_ans - 1) : ans[len_ans - i - 1] - '0' ; }
    transport[i + 1] += transport[i] / BAZA ;
    transport[i] %= BAZA ; }
  int digit(0), aux ;
  for (i = len_ans + 1 ; i >= 0 ; -- i) {
    digit = digit * BAZA + transport[i] ;
    if (i < len_fi && fi[len_fi - i - 1] == '*') {
      aux = std::min(digit, BAZA - 1 - (i == len_fi - 1)) ;
      fi[len_fi - i - 1] = '9' - aux ;
      digit -= aux ; }
    if (i < len_se && se[len_se - i - 1] == '*') {
      aux = std::min(digit, BAZA - 1 - (i == len_se - 1)) ;
      se[len_se - i - 1] = '9' - aux ;
      digit -= aux ; }
    if (i < len_ans && ans[len_ans - i - 1] == '*') {
      aux = std::min(digit, BAZA - 1 - (i == len_ans - 1)) ;
      ans[len_ans - i - 1] = '0' + aux + (i == len_ans - 1) ;
      digit -= aux ; } }
  out << fi << '\n' << se << '\n' << ans << '\n' ; }
 
int main() {
  int querrys ;
  in >> querrys ;
  while (querrys --) {
    solve_test() ; } }
