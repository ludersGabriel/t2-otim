#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include "data.hpp"

// nossa funcao de corte por otimalidade, gulosa
int greedyBound(vector<int> &selection, int i);

// Retorna o menor valor do vetor de atores
int getSmallestValue(int i);

// Função de bounding previamente fornecida pelo professor
int givenBound(vector<int> &selection, int i);

// Checa se a quantidade de atores é válida
bool isActorCountValid(int count, int i);

// Checa se infringimos a viabilidade por grupo
bool isGroupValid(vector<int> &selection, vector<int> groups);

// Soma o valor dos atores já selecionados
int f(vector<int> &selection);

void BT(int i, int count);

// Retorna atual do tempo do sistema
double timestamp(void);

// Checa se há menos atores que personagens
void characterErrorCheck();

// Lê o arquivo de entrada
void readInput();

// Checa erro de inviabilidade de grupo
void groupErrorCheck(int error);

// Imprime as mensagens de verbose mode
void verbosePrinting();

// Retorna o valor dos atores selecionados
void returnSelectedActors();

// Retorna o valor de OptSum
void returnOptSum();

#endif