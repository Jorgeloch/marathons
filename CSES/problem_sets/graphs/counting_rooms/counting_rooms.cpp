#include <bits/stdc++.h>
#include <queue>

#define FLOOR '.'
#define WALL '#'

typedef uint64_t ull;
typedef int64_t ll;

using namespace std;

int main(void) {
  // magic trick to make cpp faster in I/O operations
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, m;
  cin >> n >> m;

  // basically a matrix, where each position is a pair of a char and a bool
  // the char is the character in the map, and the bool is if it has been visited or not
  // this way we can use the same matrix to store the map and the visited status
  vector<string> map(n);
  vector<vector<bool>> visited(n, vector<bool>(m, false));

  // read the map
  for (ull i = 0; i < n; i++) {
    cin >> map[i];
  }

  pair<ull,ull> start = {0, 0};
  ull count = 0;

  // iterate over the map
  for (ull i = 0; i < n; i++) {
    for (ull j = 0; j < m; j++) {
      // ignore useless positions
      if (map[i][j] == WALL || visited[i][j]) {
        continue;
      }

      // increment counter
      count++;

      // initialize a queue to do a BFS
      start = {i, j};
      queue<pair<ull,ull>> q;
      visited[start.first][start.second] = true;
      q.push(start);

      // realize BFS to iterate over all the positions in the same room
      while (!q.empty()) {
        pair<ull,ull> current = q.front();
        q.pop();
        
        vector<ll> dx = {0, 0, 1, -1};
        vector<ll> dy = {1, -1, 0, 0};

        for (ull k = 0; k < 4; k++) {
          pair<ull,ull> next = {current.first + dx[k], current.second + dy[k]};
          // verify if its a valid position
          if (next.first < 0 || next.second < 0 || next.first >= n || next.second >= m) {
            continue;
          }
          // verify if its a wall or if it has been visited
          if (map[next.first][next.second] == WALL || visited[next.first][next.second]) {
            continue;
          }
          visited[next.first][next.second] = true;
          q.push(next);
        }
      }
    }
  }

  cout << count << "\n";
  return 0;
}
