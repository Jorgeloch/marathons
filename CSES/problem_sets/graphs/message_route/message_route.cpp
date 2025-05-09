#include <algorithm>
#include <bits/stdc++.h>

typedef uint64_t ull;
typedef int64_t ll;

using namespace std;

typedef struct {
  ll parent;
  bool visited;
  vector<ull> adj;
} node;

bool recursiveBFS(queue<ull> &q, vector<node> &n, ull destination) {
  if (q.empty()) return false;

  ull cur = q.front();
  q.pop();
  if (cur == destination) return true;

  for (ull next: n[cur].adj) {
    if (!n[next].visited) {
      n[next].visited = true;
      n[next].parent = cur;
      q.push(next);
    }
  }

  return recursiveBFS(q, n, destination);
}

vector<ull> findPath(vector<node> &n, ull start) {
  vector<ull> path;

  ll curr = start;
  while (curr != -1) {
    path.push_back(curr);
    curr = n[curr].parent;
  }
  
  reverse(path.begin(), path.end());

  return path;
}

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);

  ull n_computers, n_connections;
  cin >> n_computers >> n_connections;

  vector<node> computers(n_computers + 1, {
    .parent =  -1,
    .visited = false,
    .adj = vector<ull>()
  });

  for (ull i = 0; i < n_connections; i++) {
    ull node_i, node_j;
    cin >> node_i >> node_j;
    
    computers[node_i].adj.push_back(node_j);
    computers[node_j].adj.push_back(node_i);
  }

  queue<ull> q; 
  q.push(1);
  computers[1].visited = true;

  if (!recursiveBFS(q, computers, n_computers)) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }


  vector<ull> path = findPath(computers, n_computers);
  
  cout << path.size() << "\n";
  cout << path[0];
  for (ull i = 1; i < path.size(); i++) {
    cout << " " << path[i];
  }
  cout << "\n";

  return 0;
}
