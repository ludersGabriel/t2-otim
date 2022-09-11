#include "bb.h"

int getSmallestValue(int i){
  if(i > m) return inf;

  return actors[i].v;
}

int givenBound(vector<int>& selection, unsigned int i){
  int smallest = getSmallestValue(i);

  int sum = 0;
  int howManySelected = 0;
  for(unsigned int j = 1; j < i && j < selection.size(); j++){
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
  for(unsigned int i = 1; i < selection.size(); i++){
    if(selection[i]){
      sum += actors[i].v;
    }
  }

  return sum;
}

// groups is being passed through copy, so theres no problem modifying
bool isGroupValid(vector<int>& selection, vector<int> groups){
  for(unsigned int i = 1; i < selection.size(); i++){
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

double timestamp(void) {
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return((double)(tp.tv_sec*1.0e3 + tp.tv_nsec*1.0e-6));
}

int greedyBound(vector<int>& selection, unsigned int i){
  int sum = 0;
  int howManySelected = 0;
  for(unsigned int j = 1; j < i && j < selection.size(); j++){
    if(selection[j]){
      howManySelected++;
      sum += actors[j].v;
    } 
  }
  int howManyLeft = n - howManySelected;

  for(unsigned int j = i; j < i + howManyLeft && j < selection.size(); j++){
    sum += actors[j].v;
  }

  return sum;

}

void BT(int i, int count){
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

    for(int j = 1; j >= 0; j--){
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
          selection[i] = 1;
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

void printReport(double time){
  cerr << "Número de nós acessados: " << nodeCount << "\n";
  cerr << "Cortes por viabilidade: " << viabilityCutCount << "\n";
  cerr << "Cortes por otimalidade: " << otimalityCutCount << "\n";
  cerr << "Tempo de execução: " << time << " ms\n";
}

void printOutput(){
  vector<int> output;
  for(int i = optSelection.size() - 1; i >= 1; i--){
    if(optSelection[i]) output.push_back(actors[i].id);
  }

  sort(output.begin(), output.end());
  for(auto el : output) cout << el << ' ';

  cout << '\n' << optSum << '\n';
}
