#include <bits/stdc++.h>

typedef uint64_t ull;
typedef int64_t ll;

using namespace std;
class DisjointSet {
  ull size;
  vector<ull> parent;
  vector<ull> rank;
public:
  DisjointSet(ull size): size(size), parent(size), rank(size, 0) {
    for (ull i = 0; i < size; i++) {
      parent[i] = i;
    }
  }

  ull find(ull i) {
    if (parent[i] != i){
      parent[i] = find(parent[i]);
    }
    return parent[i];
  }

  void unite(ull i, ull j) {
    ull parent_i = find(i);
    ull parent_j = find(j);

    if (parent_i == parent_j) return;
    // includes the set of i in the set of j
    if (rank[parent_i] > rank[parent_j]){
      parent[parent_j] = parent_i;
      return;
    } 
    if (rank[parent_i] < rank[parent_j]){
      parent[parent_i] = parent_j;
      return;
    } 

    parent[parent_i] = parent_j;
    rank[parent_j]++;
  }

  unordered_set<ull> get_sets() {
    unordered_set<ull> unique_parents;
    unique_parents.reserve(size);
    for (ull i = 1; i < size; i++) {
      unique_parents.insert(find(i));
    }
    return unique_parents;
  }
};

int main (void) {
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);

  ull n_cities, n_roads;
  cin >> n_cities >> n_roads;

  DisjointSet s(n_cities + 1);

  for (ull i = 0; i < n_roads; i++) {
    ull city_i, city_j;
    cin >> city_i >> city_j;

    s.unite(city_i, city_j);
  }

  unordered_set<ull> sets = s.get_sets();
  vector<ull> sets_parents(sets.begin(), sets.end());
  sort(sets_parents.begin(), sets_parents.end());

  cout << (sets_parents.size() - 1) << "\n";
  for (ull i = 0; i + 1 < sets_parents.size(); i++) {
    cout << sets_parents[i] << " " << sets_parents[i + 1] << "\n";
  }
   
  return 0;
}
