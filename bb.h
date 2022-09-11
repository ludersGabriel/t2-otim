#ifndef BB_H
#define BB_H

#include <bits/stdc++.h>
using namespace std;

const int inf = 1987654321;

typedef struct Actor_s{
  int id;
  int v;
  int s;
  vector<int> groups;
}Actor;

#define CARACTER_ERROR 1
#define GROUP_ERROR 2

// l == num of groups
// m == num of actors
// n == num of caracters
inline int l, m, n;

inline vector<int> groups;
inline vector<Actor> actors;
inline vector<int> selection;
inline vector<int> optSelection;
inline int optSum;

inline bool defaultBound = true;
inline bool viabilityCut = true;
inline bool otimalityCut = true;

inline long nodeCount = 0;
inline long otimalityCutCount = 0;
inline long viabilityCutCount = 0;
inline int (*bound)(vector<int>&, unsigned int);


int greedyBound(vector<int>& selection, unsigned int i);
int givenBound(vector<int>& selection, unsigned int i);
void BT(int i, int count);

double timestamp(void);
void printReport(double time);
void printOutput();


#endif