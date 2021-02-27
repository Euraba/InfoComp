#include <iostream>
#include <cstdio>
#include <queue>
#include <cassert>

FILE *in = fopen("miting.in", "r"), *out = fopen("miting.out", "w") ;

const int maxk = 10 ;
const int maxn = 60 ;
const int SIGMA = 26 ;
const int INF = 1e9 ;

typedef std::pair<int, int> PII ;

int query, n, m ;
int wordLen ;
char fullWord[1 + maxk] ;
int dp[1 + maxn][1 + maxn][1 + maxn * maxn] ;

int alphaLine[1 + SIGMA] ;
int alphaCol[1 + SIGMA] ;

int line[1 + maxn * maxn] ;
int col[1 + maxn * maxn] ;
int corespIdx[1 + maxn * maxn][1 + maxn * maxn] ;
int freeCells ;

int posInWord[1 + SIGMA] ;

int readData() {
    int i, j ;
    char current ;
    fscanf(in, "%d %d %d\n", &query, &n, &m) ;
    for (i = 1 ; (current = fgetc(in)) != '\n' ; ++ i) {
        fullWord[i] = current ;
        posInWord[current - 'A' + 1] = i ;
    }
    wordLen = i - 1 ;
    for (i = 1 ; i <= n ; ++ i) {
        for (j = 1 ; j <= m ; ++ j) {
            current = fgetc(in) ;
            if (current != '#') {
                corespIdx[i][j] = ++ freeCells ;
                line[freeCells] = i ;
                col[freeCells] = j ;
            }
            if (isalpha(current)) {
                alphaLine[posInWord[current - 'A' + 1]] = i ;
                alphaCol[posInWord[current - 'A' + 1]] = j ;
            }
        }
        fgetc(in) ;
    }
    return 1 ;
}

void solveTask1() ;

void bfs(int left, int right) ;
void solveTask2() ;

void calcDp(int i, int j, int k, int dest);

void calcDp(int i, int j, int len, int k, int dest);

int main() {
    assert(readData()) ;
    if (query == 1) {
        solveTask1() ;
    } else {
        solveTask2() ;
    }
}

void solveTask1() {
    int highestLine(0), lowestLine(1 + n) ;
    int highestCol(0), lowestCol(1 + m) ;
    for (int i = 1 ; i <= wordLen ; ++ i) {
        highestLine = std::max(highestLine, alphaLine[i]) ;
        highestCol = std::max(highestCol, alphaCol[i]) ;
        lowestLine = std::min(lowestLine, alphaLine[i]) ;
        lowestCol = std::min(lowestCol, alphaCol[i]) ;
    }
    fprintf(out, "%d", (highestLine - lowestLine + 1) * (highestCol - lowestCol + 1)) ;
}

std::queue<PII> Q ;

const int dx[] = {0, -1, 0, 1, 0} ;
const int dy[] = {0, 0, 1, 0, -1} ;


void bfs(int left, int right) {
    int x, y, i ;
    int nx, ny, newCell ;
    while (!Q.empty()) {
        x = Q.front().first; y = Q.front().second ;
        Q.pop() ;
        for (i = 1 ; i <= 4 ; ++ i) {
            nx = x + dx[i] ;
            ny = y + dy[i] ;
            newCell = corespIdx[nx][ny] ;
            if (newCell && dp[left][right][newCell] > dp[left][right][corespIdx[x][y]] + 1) {
                dp[left][right][newCell] = dp[left][right][corespIdx[x][y]] + 1 ;
                Q.push({nx, ny}) ;
            }
        }
    }
}

void solveTask2() {
    int i, j, len, k, dest ;
    for (i = 1 ; i <= wordLen ; ++ i) {
        for (j = 1 ; j <= freeCells ; ++ j) {
            dp[i][i][j] = INF ;
        }
        dp[i][i][corespIdx[alphaLine[i]][alphaCol[i]]] = 0 ;
        Q.push({alphaLine[i], alphaCol[i]}) ;
        bfs(i, i) ;
    }
#ifndef INFOARENA
    std::cerr << freeCells << '\n' ;
#endif
    for (len = 2 ; len <= wordLen ; ++ len) {
        for (i = 1 ; i <= wordLen - len + 1 ; ++ i) {
            calcDp(i, j, len, k, dest);
        }
    }
    int ans(INF) ;
    for (i = 1 ; i <= freeCells ; ++ i) {
        ans = std::min(ans, dp[1][wordLen][i]) ;
#ifndef INFOARENA
        std::cerr << i << "   ->   " << dp[1][wordLen][i] << '\n' ;
#endif
    }
    if (ans == INF) {
        ans = -1 ;
    }
    fprintf(out, "%d ", ans) ;
}

void calcDp(int i, int j, int len, int k, int dest) {
    j = i + len - 1 ;
    for (dest = 1 ; dest <= freeCells ; ++ dest) {
        calcDp(i, j, k, dest);
    }
    bfs(i, j) ;
}

void calcDp(int i, int j, int k, int dest) {
    dp[i][j][dest] = INF ;
    Q.push({line[dest], col[dest]}) ;
    for (k = i ; k < j ; ++ k) {
        dp[i][j][dest] = std::min(dp[i][j][dest], dp[i][k][dest] + dp[k + 1][j][dest]) ;
    }
}
