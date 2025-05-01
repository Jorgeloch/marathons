#include <bits/stdc++.h>

typedef uint64_t ull;
typedef int64_t ll;

using namespace std;

int main(void) {
  // magic trick to make cpp faster in I/O operations
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll n, m;
  cin >> n >> m;

  // define variables to store the labyrinth start and end points
  pair<ll, ll> start, end;
  
  // define and read labyrinth
  vector<string> labyrinth(n);
  for (ll i = 0; i < n; i++) {
    cin >> labyrinth[i];
  }

  // find the start and end points
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < m; j++) {
      if (labyrinth[i][j] == 'A') {
        start = {i, j};
      } else if (labyrinth[i][j] == 'B') {
        end = {i, j};
      }
    }
  }

  // vector to store the visited cells
  vector<vector<bool>> visited(n, vector<bool>(m, false));
  // vetor to store the parent of each cell, marking the coordinates
  // of the parent and what direction we came from
  vector<vector<array<ll, 3>>> parent(n, vector<array<ll, 3>>(m, {-1, -1, -1}));

  // definig the directions for the BFS
  constexpr ll dy[4] = {-1, 1, 0, 0};
  constexpr ll dx[4] = {0, 0, -1, 1};
  // defining the directions for the output
  constexpr char dl[4] = {'U', 'D', 'L', 'R'};
  // define flag to verify if we found the end point
  bool found = false;

  // start queue for performing BFS
  queue<pair<ll, ll>> q;
  visited[start.first][start.second] = true;
  q.push(start);

  // perform BFS
  while (!q.empty()) {
    pair<ll, ll> current = q.front();
    q.pop();
    for (ll direction = 0; direction < 4; direction++) {
      pair<ll, ll> next = {current.first + dy[direction], current.second + dx[direction]};
      // verify if the next cell is within the labyrinth bounds
      if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= m) {
        continue;
      }
      // verify if the next cell is a wall or already visited
      if (labyrinth[next.first][next.second] == '#' || visited[next.first][next.second]) {
        continue;
      }

      // define the next cell as visited
      visited[next.first][next.second] = true;
      // define the parent of the next cell as beeing the current cell and the
      // direction we came from as beeing the current direction
      parent[next.first][next.second] = {current.first, current.second, direction};
      // add next to the queue
      q.push(next);

      // if we found the end point, break the loop and set the flag to true
      if (next == end) {
        found = true;
        break;
      }
    }
  }

  // if not found, print NO and return
  if (!found) {
    cout << "NO\n";
    return 0;
  }


  // if found, we need to reconstruct the path
  string path;
  // we start at the end
  pair<ll, ll> current = end;
  // we need to go back to the start
  while (current != start) {
    // at each step we need to verify the parent of the current node
    array<ll, 3> p = parent[current.first][current.second];
    // we add the direction we came from to the path
    path.push_back(dl[p[2]]);
    // update the current node to be the parent
    current = {p[0], p[1]};
  }

  // the string is backwards, so we need to reverse it
  reverse(path.begin(), path.end());

  // print output
  cout << "YES\n";
  cout << path.size() << "\n";
  cout << path << "\n";

  return 0;
}
