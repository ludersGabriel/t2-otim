#include <bits/stdc++.h>
using namespace std;

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bb.h"

void commandLineOptions(int argc, char** argv);
void readInput();

int main(int argc, char** argv){
  bound = greedyBound;
  
  commandLineOptions(argc, argv);
  
  cin >> l >> m >> n;
  if(m < n){
    cout << "Inviável\n";
    exit(CARACTER_ERROR);
  }
  
  readInput();

  sort(actors.begin() + 1, actors.end(), [](Actor a, Actor b){ return a.v < b.v; });

  double time = timestamp();
  BT(1, m);
  time = timestamp() - time;

  if(optSum == inf){
    cout << "Inviável\n";
    exit(GROUP_ERROR);
  }

  printReport(time);
  printOutput();

  return 0;
}

void commandLineOptions(int argc, char** argv){
  int option;

  while((option = getopt(argc, argv, "foah")) != -1){
    switch(option){
      case 'f':
        viabilityCut = false;
        break;
      case 'o': 
        otimalityCut = false;
        break;
      case 'a':
        bound = givenBound;
        break;
      case 'v':
        verbose = true;
        break;
      case 'h':
      default:
        fprintf (stderr, "Usage: %s -f -o -a -h\n", argv[0]);
	      exit (1) ;
    }
  }
}

void readInput(){
  groups = vector<int>(l + 1, 0);
  actors = vector<Actor>(m + 1);
  selection = vector<int>(m + 1, 1);
  optSelection = vector<int>(m + 1, 0);

  for(int i = 1; i <= m; i++){
    int v, s;
    cin >> v >> s;
    
    actors[i].v = v;
    actors[i].id = i;
    for(int j = 0; j < s; j++){
      int g;
      cin >> g;
      groups[g]++;
      actors[i].groups.push_back(g);
    }
  }

  for(unsigned int i = 1; i < groups.size(); i++){
    if(!groups[i]){
      cout << "Inviável\n";
      exit(GROUP_ERROR);
    }
  }
}