#include <bits/stdc++.h>

using namespace std;
const int sigma = 26, ms = 1e5;
// ms é a soma dos tamanhos das strings
int trie[ms][sigma];
int z; // próximo nó livre
bool terminal[ms]; // diz se o nó i representa o fim de uma palavra

// é possível guardar a quantidade de palavras que seguem por um ramo, ou algo do tipo

int init() {
  memset(trie[0], -1, sizeof trie[0]);
  z = 1;
}

int get_id(char ch) {
  return ch - 'a';
}

void insert(const string &P) {
  int cur = 0;
  for (int i = 0; i < P.size(); i++) {
    int id = get_id(P[i]);
    if (trie[cur][id] == -1) {
      memset(trie[z], -1, sizeof trie[z]);
      trie[cur][id] = z++;
    }
    cur = trie[cur][id];
  }
  terminal[cur] = true;
}

// saber se P é alguma palavra do dicionário
bool find(const string &P) {
  int cur = 0;
  for (int i = 0; i < P.size(); i++) {
    int id = get_id(P[i]);
    if (trie[cur][id] == -1) {
      return false;
    }
    cur = trie[cur][id];
  }
  return terminal[cur]; // troca pra true se quer saber se P é prefixo de alguam palavra
}
