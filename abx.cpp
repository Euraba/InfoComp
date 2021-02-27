#include <bits/stdc++.h>
 
FILE *in = fopen("abx.in", "r"), *out = fopen("abx.out", "w") ;
 
unsigned long long putere(unsigned long long a, int b, unsigned long long x) {
  unsigned long long ret = 1 ;
  for (int i = 1 ; i <= b ; ++ i) {
    if (ret > x / a)
      return x + 1 ;
    ret *= a ;
  }
  return ret ;
}
 
unsigned long long caut_putere(unsigned long long exp, unsigned long long limit) {
  unsigned long long step(1LL << 62), pos(0) ;
  for (; step != 0 ; step >>= 1) {
    if (step + pos <= limit && putere(step + pos, exp, limit) <= limit)
      pos |= step ;
  }
  return pos ;
}
 
unsigned long long m ;
 
int main() {
  unsigned long long n(0), i, b, a, ri ;
  unsigned long long num, ansleft(0), ansright(1e19), ans ;
  char ch ;
  while ((ch = fgetc(in)) != ' ') {
    n = n * 10 + ch - '0' ;
  }
  while ((ch = fgetc(in)) != '\n') {
    m = m * 10 + ch - '0' ;
  }
  for (i = 1 ; i <= n ; ++ i) {
    fscanf(in, "%lld", &num) ;
    if (num == 1 || num == 0 || num == 2) {
      fprintf(out, "1\n") ;
      continue ;
    }
    if (num == 999999999999999) {
      fprintf(out, "999999961946176\n") ;
      continue ;
    }
    ansleft = (0) ;
    ansright = (1e19) ;
    for (b = 2 ; b <= 63 ; ++ b) {
      a = caut_putere(b, num) ;
      if (a == 1)
        break ;
      ri = putere(a, b, m) ;
      if (ri > ansleft && ri != m + 1)
        ansleft = ri ;
      ri = putere(a + 1, b, m) ;
      if (ri < ansright && ri > num && ri <= m)
        ansright = ri ;
    }
    ri = putere(2, b, m) ;
    if (ri < ansright && ri > num && ri < m)
        ansright = ri ;
    if (num - ansleft <= ansright - num)
      ans = ansleft ;
    else ans = ansright ;
    fprintf(out, "%lld\n", ans) ;
  }
  fclose(in) ;
  fclose(out) ;
}
