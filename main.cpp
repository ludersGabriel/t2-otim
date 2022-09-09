#include <bits/stdc++.h>
using namespace std;

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
int l, m, n;

vector<int> groups;
vector<Actor> actors;
vector<int> selection;
vector<int> optSelection;
int optSum = inf;

bool defaultBound = true;
bool viabilityCut = true;
bool otimalityCut = true;
bool verbose = false;

long nodeCount = 0;
long otimalityCutCount = 0;
long viabilityCutCount = 0;

double timestamp(void) {
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return((double)(tp.tv_sec*1.0e3 + tp.tv_nsec*1.0e-6));
}

int greedyBound(vector<int>& selection, int i){
  int sum = 0;
  int howManySelected = 0;
  for(int j = 1; j < i && j < selection.size(); j++){
    if(selection[j]){
      howManySelected++;
      sum += actors[j].v;
    } 
  }
  int howManyLeft = n - howManySelected;

  for(int j = i; j < i + howManyLeft && j < selection.size(); j++){
    sum += actors[j].v;
  }

  return sum;

}

int (*bound)(vector<int>&, int) = greedyBound;

int getSmallestValue(int i){
  if(i > m) return inf;

  return actors[i].v;
}

int givenBound(vector<int>& selection, int i){
  int smallest = getSmallestValue(i);

  int sum = 0;
  int howManySelected = 0;
  for(int j = 1; j < i && j < selection.size(); j++){
    if(selection[j]){
      howManySelected++;
      sum += actors[j].v;
    } 
  }
  int howManyLeft = n - howManySelected;

  return sum + smallest * (howManyLeft);

}

int f(vector<int>& selection){
  int sum = 0;
  for(int i = 1; i < selection.size(); i++){
    if(selection[i]){
      sum += actors[i].v;
    }
  }

  return sum;
}

// groups is being passed through copy, so theres no problem modifying
bool isGroupValid(vector<int>& selection, vector<int> groups){
  for(int i = 1; i < selection.size(); i++){
    if(!selection[i]){
      for(auto el : actors[i].groups){
        groups[el]--;
        if(!groups[el]) return false;
      }
    }
  }

  return true;
}

bool isActorCountValid(int count, int i){
  if(count < n || count > n) return false;

  return true;
}

void BT(int i, int count){
  if(verbose) 
    // cout << "BT(" << i << ", " << count << ")\n";
  nodeCount++; 

  // leaf
  if(i > m){
    if(
      !isGroupValid(selection, groups) 
      || !isActorCountValid(count, i)
    ) return;
    
    int sum = f(selection);
    if(sum < optSum){
      optSum = sum;
      optSelection = selection;
    } 
  }
  else { 
    int boundValue = bound(selection, i);

    for(int j = 0; j <= 1; j++){
        selection[i] = j;

        if(otimalityCut && boundValue >= optSum ){
          otimalityCutCount++;
          continue;
        } 

        if(!j){
          if(viabilityCut){
            if(
              count - 1 >= n 
              && isGroupValid(selection, groups)
              && !(i + 1 > m && count - 1 > n)
            ) 
              BT(i + 1, count - 1);
            else
              viabilityCutCount++;
          }
          else BT(i + 1, count - 1);
          
        } 
        else {
          if(viabilityCut){
            if(
              !(i + 1 > m && count > n)
              && (count - n <= m - i)
            ) 
              BT(i + 1, count);
            else 
              viabilityCutCount++;
          }
          else BT(i + 1, count);
        }
    }
  }
}

void print(){
  cout << f(selection) << '\n';
  cout << "groups: ";
  for(int i = 1; i < groups.size(); i++) cout << groups[i] << ' ';
  cout << "\nActors\n";
  for(int i = 1; i <= m; i++){
    cout << "Actor " << i << ": " << actors[i].v << " -> ";
    for(int j = 0; j < actors[i].groups.size(); j++){
      cout << actors[i].groups[j] << ' ';
    }
    cout << '\n';
  } 
}

int main(int argc, char** argv){
  int option;

  while((option = getopt(argc, argv, "foavh")) != -1){
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
        fprintf (stderr, "Usage: %s -f -o -a -v -h\n", argv[0]);
	      exit (1) ;
    }
  }
  
  cin >> l >> m >> n;
  if(m < n){
    cout << "Inviável\n";
    exit(CARACTER_ERROR);
  }
  
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

  for(int i = 1; i < groups.size(); i++){
    if(!groups[i]){
      cout << "Inviável\n";
      exit(GROUP_ERROR);
    }
  }

  sort(actors.begin() + 1, actors.end(), [](Actor a, Actor b){ return a.v < b.v; });

  double time = timestamp();
  BT(1, m);
  time = timestamp() - time;

  if(optSum == inf){
    cout << "Inviável\n";
    exit(GROUP_ERROR);
  }

  if(verbose){
    cout << "Número de nós acessados: " << nodeCount << "\n";
    cout << "Cortes por viabilidade: " << viabilityCutCount << "\n";
    cout << "Cortes por otimalidade: " << otimalityCutCount << "\n";
    cout << "Tempo de execução: " << time << " ms\n";
    
    cout << "Atores selecionados e soma ótima: \n";
  }

  vector<int> output;
  for(int i = optSelection.size() - 1; i >= 1; i--){
    if(optSelection[i]) output.push_back(actors[i].id);
  }

  sort(output.begin(), output.end());
  for(auto el : output) cout << el << ' ';

  cout << '\n' << optSum << '\n';

  return 0;
}