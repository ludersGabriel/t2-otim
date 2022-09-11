#ifndef __DATA__
#define __DATA__
using namespace std;

#include <bits/stdc++.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Structs ======================================================================

// struct que define um ator
typedef struct Actor_s
{
    int id;             // Identificador
    int v;              // Valor
    int s;              // Tamanho do vetor de grupos
    vector<int> groups; // Vetor de grupos
} Actor;

// Erros ========================================================================

#define CARACTER_ERROR 1
#define GROUP_ERROR 2

// Constantes ===================================================================

const int inf = 1987654321;

// Variáveis globais ============================================================

inline int l; // l == número de grupos
inline int m; // m == número de atores
inline int n; // n == número de personagens

inline vector<int> groups;       // vetor de grupos
inline vector<Actor> actors;     // vetor de atores
inline vector<int> selection;    // vetor caracterização da instância
inline vector<int> optSelection; // vetor caracterização ótimo da instância
inline int optSum = inf;         // soma ótima, inicializada com infinito

inline bool viabilityCut = true;
inline bool otimalityCut = true;
inline bool verbose = false;

inline long nodeCount = 0;
inline long otimalityCutCount = 0;
inline long viabilityCutCount = 0;

#endif
