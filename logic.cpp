#include <iostream>
#include <fstream>

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <bitset>

std::fstream in ("logic.in", std::ios::in | std::ios::binary) ;
std::fstream out ("logic.out", std::ios::out) ;

class BooleanExpresion {
private :
    static const int SIGMA = 26 ;
    std::string exp ;
    bool upd[1 + SIGMA] ;
    int point ;
    char currentChar() {
        while (exp[point] == ' ') {
            advance() ;
        }
        return exp[point] ;
    }
    void advance() {
        point ++ ;
    }
    char notSign, BASE ;

public :
    __attribute__ ( (always_inline)) BooleanExpresion(std::string aux) {
        exp = aux ;
        point = 0 ;
        /// Change the NOT sign here
        notSign = '~' ;
        /// it does not work with both upper and lower at the same time
        BASE = 'a' ;
    }

    void reset(int pos = 0) {
        this ->point = pos ;
    }

    bool evaluate() {
        bool currVal = xorFactor() ;
        while (currentChar() == '|') {
            advance() ;
            currVal |= xorFactor() ;
            //advance() ;
        }
        return currVal ;
    }

    bool xorFactor() {
        bool currVal = andFactor() ;
        while (currentChar() == '^') {
            advance() ;
            currVal ^= andFactor() ;
            //advance() ;
        }
        return currVal ;
    }

    bool andFactor() {
        bool currVal = notFactor() ;
        while (currentChar() == '&') {
            advance() ;
            currVal &= notFactor() ;
            //advance() ;
        }
        return currVal ;
    }

    bool notFactor() {
        bool currVal ;
        if (currentChar() == '(') {
            advance() ;
            currVal = evaluate() ;
            advance() ;
        } else {
            if (currentChar() == '0') {
                advance() ;
                currVal = 0 ;
            } else if (currentChar() == '1') {
                advance() ;
                currVal = 1 ;
            } else if (currentChar() == notSign) {
                advance() ;
                currVal = !notFactor() ;
            } else {
                currVal = upd[currentChar() - BASE] ;
                advance() ;
            }
        }
        return currVal ;
    }

    void update(char let, bool value) {
        upd[let - BASE] = value ;
    }
};

void solve() {
    std::string a, b ;
    in >> a >> b ;
    std::map<char, int> mp1, mp2 ;
    for (auto it : a) {
        mp1[it] ++ ;
    }
    for (auto it : b) {
        mp2[it] ++ ;
    }
    int cnt(0) ;
    std::vector<char> vv ;
    std::string x ;
    for (char c = 'a' ; c <= 'z' ; ++ c) {
        if (mp1[c]) {
            if (!mp2[c]) {
                out << "diferite\n" ;
                return ;
            }
            ++ cnt ;
            vv.push_back(c) ;
        } else {
            if (mp2[c]) {
                out << "diferite\n" ;
                return ;
            }
        }
    }
    BooleanExpresion sa(a), sb(b) ;
    //out << "Test :\n" ;
    for (int i = 1 ; i < (1 << cnt) ; ++ i) {
        for (int j = cnt - 1 ; j >= 0 ; -- j) {
            sa.update([vv[j] - 'a'], (i >> j) & 1) ;
            sb.update([vv[j] - 'a'], (i >> j) & 1) ;
        }
        bool fi = sa.evaluate() ;
        bool se = sb.evaluate() ;
        sa.reset(), sb.reset() ;
        //out << std::bitset<5>(i).to_string() << "  -> " << fi << " , " << se << '\n' ;
        if (fi != se) {
            out << "diferite\n" ;
            return ;
        }
    }
    out << "egale\n" ;
}

int main() {
    int tests(1) ;
    in >> tests ;
    for ( ; tests ; -- tests) {
        solve() ;
    }
}
