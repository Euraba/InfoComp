#include <cstdio>
#include <cstdlib>
#include <queue>
#include <iostream>

FILE *in = fopen("panda.in", "r"), *out = fopen("panda.out", "w") ;

const int nmax = 500 ;

bool food[1 + nmax][1 + nmax] ;
bool road[1 + nmax][1 + nmax] ;

const int dx[] = {0, 1, 0, -1, 0};
const int dy[] = {0, 0, 1, 0, -1};

int query, n, m, specialCells, L, C, k, s ;

struct Cell {
    int l, c ;
    Cell() : l(0), c(0) {}
    Cell(const int _l, const int _c) {
        this ->l = _l ;
        this ->c = _c ;
    }
};

int distance[1 + nmax][1 + nmax] ;
int minDist(1e9), foodCells ;

void BFS(int l, int c) {
    std::queue<Cell> cells ;
    cells.push(Cell(l, c)) ;
    int i ;
    distance[l][c] = 1 ;
    auto inbounds = [&](Cell aux) -> bool {
        return 1 <= aux.l && aux.l <= n && 1 <= aux.c && aux.c <= m ;
    };
    while (!cells.empty()) {
        Cell top = cells.front() ;
        cells.pop() ;
#ifndef INFOARENA
        std::cerr << top.l << ' ' << top.c << '\n' ;
#endif
        for(i = 1 ; i <= 4 ; ++ i) {
            Cell nw(top.l + dx[i], top.c + dy[i]) ;
            if (inbounds(nw) && road[nw.l][nw.c] && !distance[nw.l][nw.c]) {
                distance[nw.l][nw.c] = distance[top.l][top.c] + 1 ;
                cells.push(nw) ;
                if (food[nw.l][nw.c]) {
#ifndef INFOARENA
                    std::cerr << "Am gasit mancare la " << nw.l << ":" << nw.c << '\n' ;
                    std::cerr << "Este la dist " << distance[nw.l][nw.c] << '\n' ;
#endif
                    if (distance[nw.l][nw.c] < minDist) {
                        minDist = distance[nw.l][nw.c] ;
                        foodCells = 1 ;
                    } else if (distance[nw.l][nw.c] == minDist) {
                        foodCells ++ ;
                    }
                }
            }
        }
    }
    minDist -- ;
}

int main() {
    fscanf(in, "%d\n%d %d %d\n%d %d %d %d\n", &query, &n, &m, &specialCells, &L, &C, &k, &s) ;
    int i, j, x, y ;
    for (i = 1 ; i <= specialCells ; ++ i) {
        fscanf(in, "%d %d\n", &x, &y) ;
        food[x][y] = 1 ;
    }
    int mask((1 << s) - 1) ;
    k = (k & mask) ^ mask ;
    int goodCells(0) ;
    for (i = 1 ; i <= n ; ++ i) {
        for (j = 1 ; j <= m ; ++ j) {
            fscanf(in, "%d ", &x) ;
            x = x & mask ;
            road[i][j] = (x == k) ;
            goodCells += road[i][j] ;
        }
    }
#ifndef INFOARENA
    for (i = 1 ; i <= n ; ++ i) {
        for (j = 1 ; j <= m ; ++ j) {
            std::cerr << road[i][j] ;
        }
        std::cerr << '\n' ;
    }
#endif
    if (query == 1) {
        fprintf(out, "%d", goodCells - 1) ;
        exit(0) ;
    }
    BFS(L, C) ;
    fprintf(out, "%d %d", minDist, foodCells) ;
}
