#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;

// OBS: Estou fazer uma solução com ull deixando dar overflow.
// Existem questões que fazem casos para que esse hash dê conflito
// Neste caso, recomendo usar um módulo para os ex: mod = 1e9 + 7
// assim phash[i] = phash[i] % mod

// Em alguns casos é util usar double (ou mais) hash. Quando vc usa dois ou mais
// mod's, assim um hash fira uma v-upla (n é o número de modulos)
// Ou seja phash[i] = (phash[i] % mod1, phash[i] % mod2, phash[i] % mod3, ...)
// 2 já é bom o bastante na maioria dos casos
// lembrando que para cada modulo o pot é diferente.

// VOCÊ TAMBÉM PODE VARIAR A BASE

const int ms = 1e5 + 10;
const ull base = 37; // um primo maior que o maior valor de um elemento

ull pot[ms]; 

void initPot() {
  pot[0] = 1;
  for (int i = 0; i + 1 < ms; i++) {
    pot[i+1] = pot[i] * base; 
  }
}

// não pode mapear no 0
ull get_id(char ch) {
  return ch - 'a' + 1;
}

vector<ull> buildHash(const string T) {
  vector<ull> phash(T.size() + 1, 0);
  phash[0] = 0;
  for (int i = 0; i < T.size(); i++) {
    phash[i + 1] = phash[i] * base + get_id(T[i]);
  } 
}

// subhash da posição [l, r] do texto
// lembrando que o prefixo do texto terminando na posição i está na posição i+1 de phash
ull subHash(const vector<ull> &phash, int l, int r) {
  int size = r - l + 1;
  return phash[r + 1] - phash[l] * pot[size];
}

// comparar duas strings usando os vectores de hash
// O(logn), dado que os vetores de hash já foram criados
// a < b
bool compair(const string &a, const vector<ull> hashA, const string &b, const vector<ull> hashB) {
  int lo = 0, hi = min(a.size(), b.size());
  while (hi - lo > 1) {
    int md = (lo + hi) / 2;
    if (hashA[md + 1] == hashB[md + 1]) {
      lo = md + 1;
    } else {
      hi = md;
    }
  }
  int first = lo; // primeira posição que os prefixos são diferentes
  if (hashA[lo + 1] == hashB[lo + 1]) {
    first = hi;
  }

  if (first == min(a.size(), b.size())) {
    return a.size() < b.size();
  } else {
    return a[first] < b[first];
  }
}
