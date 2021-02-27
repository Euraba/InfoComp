#include <bits/stdc++.h>
 
const double PI = acos(-1);
 
struct Point {
  double x;
  double y; };
 
double Distance(Point a, Point b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
 
double Bucata_Galbena(double r, double a, double b, double c) {
  return r * r * acos((a * a + b * b - c * c) / (2 * a * b)); }
 
double Intersection(Point p1, double r1, Point p2, double r2) {
  double d = Distance(p1, p2);
  if (d >= r1 + r2)
    return 0;
  if (d + r1 <= r2 || d + r2 <= r1)
    return PI * std::min(r1, r2) * std::min(r1, r2);
  double s = (r1 + r2 + d) / 2;
  return Bucata_Galbena(r1, r1, d, r2) + Bucata_Galbena(r2, r2, d, r1) - 2 * sqrt(s * (s - r1) * (s - r2) * (s - d)); }
 
int main() {
  freopen("cercuri3.in", "r", stdin);
  freopen("cercuri3.out", "w", stdout);
  int querys;
  scanf("%d", &querys);
  Point p1, p2;
  while (querys --) {
    double r1, r2, x;
    scanf("%lf%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &r1, &p2.x, &p2.y, &r2, &x);
    if (Intersection(p1, r1, p2, r2) > x)
      printf("DA\n");
    else
      printf("NU\n"); }
  return 0; }
