#include <bits/stdc++.h>
#include <cstdint>

typedef uint64_t ull;
typedef int64_t ll;

using namespace std;

ull start, finish;

bool dfs_visit(vector<vector<ull>> &adj, vector<bool> &visited, vector<ull> &parents, ull current, ull parent) {
  visited[current] = true;
  // iterate over all reachable nodes from node i, if found a cycle return true
  for (ull child: adj[current]) {
    if (!visited[child]) {
      parents[child] = current;
      if (dfs_visit(adj, visited, parents, child, current)) {
        return true;
      }
    }
    else if (child != parent) {
      start = child;
      finish = current;
      return true;
    }
  }
  return false;
}

bool dfs(vector<vector<ull>> &adj, vector<bool> &visited, vector<ull> &parents) {
  ull N = visited.size();
  for (ull i = 1; i < N; i++) {
    if (!visited[i]) {
      if (dfs_visit(adj, visited, parents, i, 0)) return true;
    }
  }

  return false;
}

vector<ull> find_path (vector<ull> &parents) {
  vector<ull> path;

  ull curr = finish;
  while (curr != start) {
    path.push_back(curr);
    curr = parents[curr];
  }
  path.push_back(start);

  reverse(path.begin(), path.end());
  path.push_back(start);

  return path;
}

void print_path (vector<ull> &path) {
  cout << path.size() << "\n";
  cout << path[0];
  for (ull i = 1; i < path.size(); i++) {
    cout << " " << path[i];
  }
  cout << "\n";
}

int main (void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n_cities, n_roads;
  cin >> n_cities >> n_roads;

  vector<vector<ull>> adj(n_cities + 1);
  vector<bool> visited(n_cities + 1, false);
  vector<ull> parents(n_cities + 1, 0);

  for (ull i = 0; i < n_roads; i++) {
    ull city_1, city_2;
    cin >> city_1 >> city_2;

    adj[city_1].push_back(city_2);
    adj[city_2].push_back(city_1);
  }

  if (dfs(adj, visited, parents)) {
    vector<ull>path = find_path(parents);
    print_path(path);
    return 0;
  }


  cout << "IMPOSSIBLE\n";
  return 0;
}
