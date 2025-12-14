#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  // Function to find the shortest distance of all the vertices
  // from the source vertex S.
  vector<int> dijkstra(int V, vector<vector<int>> adj[], int S) {
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    vector<int> dist(V, INT_MAX);

    dist[S] = 0;
    pq.push({0, S});

    while (!pq.empty()) {
      int d = pq.top().first;
      int u = pq.top().second;
      pq.pop();

      if (d > dist[u])
        continue;

      for (auto &edge : adj[u]) {
        int v = edge[0];
        int w = edge[1];

        if (dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
          pq.push({dist[v], v});
        }
      }
    }
    return dist;
  }
};

int main() {
  Solution sol;
  int V = 3, S = 2;
  vector<vector<int>> adj[3];

  // 2->1 w=1
  adj[2].push_back({1, 1});
  // 2->0 w=6
  adj[2].push_back({0, 6});
  // 1->0 w=3
  adj[1].push_back({0, 3});

  vector<int> res = sol.dijkstra(V, adj, S);
  cout << "Distances: ";
  for (int d : res)
    cout << d << " ";
  cout << endl; // Expect: 4 1 0

  return 0;
}
