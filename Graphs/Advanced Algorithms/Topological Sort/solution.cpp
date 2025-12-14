#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> inDegree(numCourses, 0);

    for (auto &edge : prerequisites) {
      adj[edge[1]].push_back(edge[0]);
      inDegree[edge[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
      if (inDegree[i] == 0)
        q.push(i);
    }

    vector<int> order;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      order.push_back(u);

      for (int v : adj[u]) {
        inDegree[v]--;
        if (inDegree[v] == 0)
          q.push(v);
      }
    }

    if (order.size() == numCourses)
      return order;
    return {};
  }
};

void printVector(const vector<int> &v) {
  cout << "[";
  for (size_t i = 0; i < v.size(); ++i) {
    cout << v[i] << (i < v.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  int n1 = 2;
  vector<vector<int>> pre1 = {{1, 0}};
  cout << "Order 1: ";
  printVector(sol.findOrder(n1, pre1)); // Expect [0,1]

  int n2 = 4;
  vector<vector<int>> pre2 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
  cout << "Order 2: ";
  printVector(sol.findOrder(n2, pre2)); // Expect [0,1,2,3] or [0,2,1,3]

  int n3 = 2;
  vector<vector<int>> pre3 = {{1, 0}, {0, 1}}; // Cycle
  cout << "Order 3: ";
  printVector(sol.findOrder(n3, pre3)); // Expect []

  return 0;
}
