#include <bits/stdc++.h>
 
FILE *in = fopen("ec.in", "r"), *out = fopen("ec.out", "w") ;
 
const int SIZE = (1 << 16) ;
 
char buff[SIZE] ;
int point ;
 
int ap[20005] ;
 
#define ap (ap + 10001)
 
void advance()  {
  if (point == SIZE) {
    fread(buff, SIZE, 1, in) ;
    point = 0 ;
  } else point ++ ;
}
 
int read() {
  int ret(0) ;
  for ( ; !isdigit(buff[point]) ; advance()) ;
  for ( ; isdigit(buff[point]) ; advance()) {
    ret = (ret << 3) + (ret << 1) + (buff[point] - '0') ;
  }
  return ret ;
}
 
int ec1, ec2, ec1s, ec2s ;
 
void solve() {
  int a = read() ;
  int b, c ;
  advance() ;
  int rhs, delta, sol ;
  if (buff[point] == '+') {
    advance() ;
    ec1 ++ ;
    b = read() ; advance() ;
    rhs = read() ;
    sol = (rhs - b) ;
    if (a == 0) {
      if (rhs == b) {
        //ec1s ++ ;
        //std::cerr << "0x+" << b << "=" << rhs << '\n' ;
      }
      return ;
    }
    if (sol % a != 0) {return ; }
    sol /= a ;
    ec1s += (ap[sol] > 0) ;
    //if (ap[sol] > 0)
    //std::cerr << a << "x+" << b << "=" << rhs << '\n' ;
  } else {
    ec2 ++ ;
    advance() ; advance() ; advance() ;
    b = read() ; advance() ; advance() ;
    c = read() ; advance() ;
    rhs = read() ;
    c -= rhs ;
    /// x1,2 = (-b +- sqrt(b * b - 4 * a * c)) / 2a
    if (b *b < 4 * a * c) {
      return ;
    }
    delta = sqrt(b * b - 4 * a * c) ;
    if (delta * delta != b * b - 4 * a *  c) {
      return ;
    }
    int pos = 0 ;
    if (a == 0) {
      if (b == 0) {
        if (c == 0) {
         // ec2s ++ ;
        }
        return ;
      } else {
        sol = -c / b ;
        if (sol * b == -c) {
          if (ap[sol]) {
            ec2s ++ ;
          }
        }
      }
      return ;
    }
    sol = (-b + delta) ;
    if (a != 0 && sol % (2 * a) == 0) {
      sol /= 2 * a ;
      pos += (ap[sol] > 0) ;
    }
    sol = (-b - delta) ;
    if (a != 0 && sol % (2 * a) == 0) {
      sol /= 2 * a ;
      pos += (ap[sol] > 0) ;
    }
    if (pos == 2) {
      ec2s ++ ;
    }
  }
}
 
int main() {
  int n, k, val ;
  fscanf(in, "%d %d", &n, &k) ;
  register int i, j ;
  for (i = 1 ; i <= n ; ++ i) {
    for (j = 1 ; j < n ; ++ j) {
      fscanf(in, "%d ", &val) ;
      ap[val] ++ ;
    }
    fscanf(in, "%d\n", &val) ;
    ap[val] ++ ;
  }
  for (i = 1 ; i <= k ; ++ i) {
    solve() ;
  }
  fprintf(out, "%d %d\n%d %d", ec1, ec1s, ec2, ec2s) ;
}
