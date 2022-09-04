#include <bits/stdc++.h>
using namespace std;

typedef struct Actor_s{
  int id;
  int v;
  int s;
  vector<int> groups;
}Actor;

typedef struct Group_s{
  int id;
  bool used;

  Group_s() {};
  Group_s(int id){
    this->id = id;
    used = false;
  };

}Group;

typedef struct GroupList_s{
  vector<Group> groups;
  int usedCount;
  int amount;

  GroupList_s(int groupSize) {
    groups = vector<Group> (groupSize + 1);
    usedCount = 0;
    amount = groupSize;
  };

}GroupList;

int main(){
  
  // l == num of groups
  // m == num of actors
  // n == num of caracters
  int l, m, n;

  cin >> l >> m >> n;
  GroupList groups(l);
  vector<Actor> actors (m + 1);
  vector<int> control (m + 1, 0);

  for(int i = 1; i <= l; i++){
    groups.groups[i] = Group(i);
  }

  for(int i = 1; i <= m; i++){
    actors[i].id = i;
    cin >> actors[i].v >> actors[i].s;

    for(int j = 0; j < actors[i].s; j++){
      int id;
      cin >> id;
      actors[i].groups.push_back(id);
    }
  }

  for(auto actor : actors){
    cout << "ator " << actor.id << " (cache, grupos): " << actor.v << ' ';

    for(auto group : actor.groups) cout << group << ' '; 
    cout << endl;
  }


  return 0;
}