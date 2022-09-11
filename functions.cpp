#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.hpp"

// Chute otimista, caucula e nao resolve o problema
// nossa funcao de corte por otimalidade, gulosa
int greedyBound(vector<int> &selection, int i)
{
    int sum = 0;
    int howManySelected = 0;
    for (int j = 1; j < i && j < selection.size(); j++)
    {
        // se ele foi colocado, soma o valor do ator e aumenta quantos foram escolhidos
        if (selection[j])
        {
            howManySelected++;
            sum += ::actors[j].v; // soma o valor dos atores | menor entre o 3 e o 4
        }
    }
    // quantos faltam pros selecionados
    int howManyLeft = ::n - howManySelected;

    // ignora a viabilidade dos grupos
    // vai até i + quantos faltam
    for (int j = i; j < i + howManyLeft && j < selection.size(); j++)
    {
        sum += ::actors[j].v; // menores valores de atores que eu ainda nao decidi
    }

    return sum;
}

// Retorna o menor valor do vetor de atores
int getSmallestValue(int i)
{
    // Checa se i já estourou o limite do vetor de atores
    if (i > m)
        return inf;

    return ::actors[i].v;
}

// Função de bounding previamente fornecida pelo professor
int givenBound(vector<int> &selection, int i)
{
    int smallest = getSmallestValue(i);

    int sum = 0;
    int howManySelected = 0;
    for (int j = 1; j < i && j < selection.size(); j++)
    {
        if (selection[j])
        {
            howManySelected++;
            sum += ::actors[j].v;
        }
    }
    int howManyLeft = ::n - howManySelected;

    return sum + smallest * (howManyLeft);
}

// Checa se infringimos a viabilidade por grupo
//  ** groups is being passed through copy, so theres no problem modifying
bool isGroupValid(vector<int> &selection, vector<int> groups)
{
    for (int i = 1; i < selection.size(); i++)
    {
        if (!selection[i])
        {
            for (auto el : ::actors[i].groups)
            {
                groups[el]--;
                if (!groups[el])
                    return false;
            }
        }
    }

    return true;
}

// Checa se a quantidade de atores é válida
bool isActorCountValid(int count, int i)
{
    if (count < n || count > n)
        return false;

    return true;
}

// Soma o valor dos atores já selecionados
int f(vector<int> &selection)
{
    int sum = 0;
    for (int i = 1; i < selection.size(); i++)
    {
        if (selection[i])
        {
            sum += ::actors[i].v;
        }
    }

    return sum;
}

// Retorna atual do tempo do sistema
double timestamp(void)
{
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    return ((double)(tp.tv_sec * 1.0e3 + tp.tv_nsec * 1.0e-6));
}

// Checa se há menos atores que personagens
void characterErrorCheck()
{
    if (::m < ::n)
    {
        cout << "Inviável\n";
        exit(CARACTER_ERROR);
    }
}

// Lê o arquivo de entrada
void readInput()
{
    // Para cada ator
    for (int i = 1; i <= ::m; i++)
    {
        int v, s;
        cin >> v >> s;

        ::actors[i].v = v;
        ::actors[i].id = i;
        for (int j = 0; j < s; j++)
        {
            int g;
            cin >> g;
            ::groups[g]++;
            ::actors[i].groups.push_back(g);
        }
    }
}

// Checa erro de inviabilidade de grupo
void groupErrorCheck(int error)
{
    if (error == 1)
    {
        for (int i = 1; i < ::groups.size(); i++)
        {
            if (!::groups[i])
            {
                cout << "Inviável\n";
                exit(GROUP_ERROR);
            }
        }
    }

    if (error == 2)
    {
        if (::optSum == inf)
        {
            cout << "Inviável\n";
            exit(GROUP_ERROR);
        }
    }
}

// Imprime as mensagens de verbose mode
void verbosePrinting()
{
    if (::verbose)
    {
        cout << "Número de nós acessados: " << ::nodeCount << "\n";
        cout << "Cortes por viabilidade: " << ::viabilityCutCount << "\n";
        cout << "Cortes por otimalidade: " << ::otimalityCutCount << "\n";
        cout << "Tempo de execução: " << time << " ms\n";
        cout << "Atores selecionados e soma ótima: \n";
    }
}

// Retorna o valor dos atores selecionados
void returnSelectedActors()
{
    vector<int> output;
    for (int i = ::optSelection.size() - 1; i >= 1; i--)
    {
        if (::optSelection[i])
            output.push_back(::actors[i].id);
    }

    sort(output.begin(), output.end());
    for (auto el : output)
        cout << el << ' ';
}

// Retorna o valor de OptSum
void returnOptSum()
{
    cout << '\n'
         << ::optSum << '\n';
}