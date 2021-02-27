#include <bits/stdc++.h>
 
/*---------OPEN_FILES----------*/
 
/*FILE *in = fopen("rk.in", "r"), *out = fopen("rk.out", "w") ;*/
 
std::fstream in ("rk.in", std::ios::in) ;
std::fstream out ("rk.out", std::ios::out) ;
 
/*---------ABORDARI------------*/
 
/// brut ~ 15 puncte
/// hashuri - nu sunt destul de rapide
/// Abordare Trie - 100 de puncte
/// | complexitate(log2(MAX)) timp si O(cati biti sunt maxim) memorie
 
/*-------INITIALIZARI----------*/
 
struct Trie {
        int total ; ///cate numere au configuratia curenta
        Trie *fii[2] ; /// fii[0] si fii[1] ca si biti
        ///                 1
        ///                / \
        ///               0   1                       TRIE IS GOOD
        ///              / \   \
        ///             0   1   1
        Trie() {
                fii[0] = fii[1] = NULL ;
                total = 0 ;
        }
};
 
Trie *root = new Trie ;
 
/*-------Trie Functions--------*/
 
void Insert_in_trie(Trie *node, int numar, int level) {
        node->total ++ ;
        if (level == 0) {
                return ;
        }
        int bit = numar & 1 ; ///luam LSB
        if (node->fii[bit] == NULL) {
                node->fii[bit] = new Trie ; ///cream fiu in cazul in care e prima data cand avem aceasta configuratie
        }
        Insert_in_trie(node->fii[bit], numar >> 1, level - 1) ; ///continuam pe radacina
}
 
int Get_mod_in_trie(Trie *node, int numar, int level) {
        if (level == 0) /// am ajuns la final
                return node->total ; ///returnam cate numere sunt bune
        int bit = numar & 1 ; /// luam LSB
        if (node->fii[bit] == NULL) { /// nu exista numar cu configuratia curenta
                        return 0 ; ///ceea ce inseamna ca raspunsul este 0
        }
        return Get_mod_in_trie(node->fii[bit], numar >> 1, level - 1) ; ///continuam pe radacina
}
 
/*----------PROGRAM------------*/
 
int main() {
        int n, r, k, i, num ;
        in >> n ;
        for (i = 1 ; i <= n ; ++ i) {
                ///fscanf(in, "%d", &num) ; ///citim numarul
                in >> num ;
                Insert_in_trie(root, num, 32) ; ///il bagam in trie
        }
        int Q ;
        in >> Q ;
        while (Q --) {
                in >> r >> k ;
                int ans = Get_mod_in_trie(root, r, k) ; ///luam raspunsul cu ajutorul trie
                out << ans << '\n' ; ///doamne ajuta
        }
}
