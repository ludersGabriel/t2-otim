#include <bits/stdc++.h>
using namespace std;

#include "data.hpp"
#include "functions.hpp"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ponteiro pra nossa função de bound
int (*bound)(vector<int> &, int) = greedyBound;

void BT(int i, int count)
{
  // if (::verbose)
  //   cout << "BT(" << i << ", " << count << ")\n"; // Print de debugging
  // ::nodeCount++;

  // Folha
  if (i > ::m)
  {
    if (
        !isGroupValid(::selection, ::groups) || !isActorCountValid(count, i))
      return;

    // Checa a soma pela função F
    int sum = f(::selection);
    // Se for menor, atualiza a soma
    if (sum < ::optSum)
    {
      ::optSum = sum;
      ::optSelection = ::selection;
    }
  }
  else
  {
    int boundValue = bound(::selection, i);

    for (int j = 1; j >= 0; j--)
    {
      ::selection[i] = j;

      // Se checagem de otimalidade está ligada
      if (::otimalityCut && boundValue >= ::optSum)
      {
        ::otimalityCutCount++; // corte por otimalidade
        continue;
      }

      if (!j)
      {
        if (::viabilityCut)
        {
          // Se minhas checagens são válidas
          if (
              count - 1 >= ::n && isGroupValid(::selection, ::groups) // Checa se a seleção de grupos é valida
              && !(i + 1 > ::m && count - 1 > n)                      // Quando vou entrar numa folha | mais atores selecionados do que personagens
          )
            BT(i + 1, count - 1);
          else // faço um corte
            ::viabilityCutCount++;
        }
        else
          BT(i + 1, count - 1);
      }
      else
      {
        if (::viabilityCut)
        {
          if (                                                      // checa as viabilidades
              !(i + 1 > m && count > ::n) && (count - ::n <= m - i) // se eu ainda tenho personagens o suficiente
          )
            BT(i + 1, count);
          else
            ::viabilityCutCount++;
        }
        else
          BT(i + 1, count); // mantem o mesmo count e decidir pro próximo ator
      }
    }
  }
}

int main(int argc, char **argv)
{

  // Lê os parâmetros da entrada
  int option;
  while ((option = getopt(argc, argv, "foavh")) != -1)
  {
    switch (option)
    {
    case 'f':
      ::viabilityCut = false;
      break;
    case 'o':
      ::otimalityCut = false;
      break;
    case 'a':
      bound = givenBound;
      break;
    case 'v':
      ::verbose = true;
      break;
    case 'h':
    default:
      fprintf(stderr, "Usage: %s -f -o -a -v -h\n", argv[0]);
      exit(1);
    }
  }

  // lê o número de grupos, atores e personagens.
  cin >> ::l >> ::m >> ::n;

  characterErrorCheck(); // Checa se há menos atores que personagens

  // Inicializa os vetores
  ::groups = vector<int>(l + 1, 0);
  ::actors = vector<Actor>(m + 1);
  ::selection = vector<int>(m + 1, 1);
  ::optSelection = vector<int>(m + 1, 0);

  // Lê o arquivo de entrada
  readInput();

  groupErrorCheck(1); // Checa erro de inviabilidade de grupo

  // Ordena o vetor de atores
  sort(::actors.begin() + 1, ::actors.end(), [](Actor a, Actor b)
       { return a.v < b.v; });

  // Chama a recursão e calcula o tempo de execução
  double time = timestamp();
  BT(1, m);
  time = timestamp() - time;

  groupErrorCheck(2); // Checa erro de inviabilidade de grupo
  verbosePrinting();  // Imprime as mensagens de verbose mode

  returnSelectedActors(); // Imprime o valor dos atores selecionados
  returnOptSum();         // Retorna o valor de OptSum

  return 0;
}