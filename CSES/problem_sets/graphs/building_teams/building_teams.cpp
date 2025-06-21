#include <bits/stdc++.h>

typedef uint64_t ull;
typedef int64_t ll;

using namespace std;

typedef struct {
  ull parent;
  ull color;
  vector<ull> friends;
} pupil;

bool recursiveBFS(queue<ull> &q, vector<pupil> &pupils) {
  if (q.empty()) return true;

  ull current = q.front();
  q.pop();

  for (ull friend_id : pupils[current].friends) {
    if (pupils[friend_id].color == 0) {
      pupils[friend_id].color = 3 - pupils[current].color;
      pupils[friend_id].parent = current;
      q.push(friend_id);
    }
    if (pupils[friend_id].color == pupils[current].color) {
      return false;
    }
  }

  return recursiveBFS(q, pupils);
}

int main (void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n_pupils, n_relations;
  cin >> n_pupils >> n_relations;

  vector<pupil> pupils(n_pupils + 1, {
    .parent = 0,
    .color = 0,
    .friends = vector<ull>()
  });

  for (ull i = 0; i < n_relations; i++) {
    ull pupil_i, pupil_j;
    cin >> pupil_i >> pupil_j;

    pupils[pupil_i].friends.push_back(pupil_j);
    pupils[pupil_j].friends.push_back(pupil_i);
  }
  

  queue<ull> q;

  for (ull i = 1; i <= n_pupils; i++) {
    if (pupils[i].color != 0) continue;

    pupils[i].color = 1;
    q.push(i);

    if (!recursiveBFS(q, pupils)) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
  }

  cout << pupils[1].color;
  for (ull i = 2; i <= n_pupils; i++) {
    cout << " " << pupils[i].color;
  }
  cout << "\n";

  return 0;
}
