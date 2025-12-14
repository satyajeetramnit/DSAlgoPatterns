#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  int findMaximizedCapital(int k, int w, vector<int> &profits,
                           vector<int> &capital) {
    int n = profits.size();
    vector<pair<int, int>> projects;
    for (int i = 0; i < n; i++) {
      projects.push_back({capital[i], profits[i]});
    }

    // Sort by capital cost
    sort(projects.begin(), projects.end());

    priority_queue<int> maxProfit;
    int i = 0;

    while (k--) {
      while (i < n && projects[i].first <= w) {
        maxProfit.push(projects[i].second);
        i++;
      }

      if (maxProfit.empty())
        break;

      w += maxProfit.top();
      maxProfit.pop();
    }

    return w;
  }
};

int main() {
  Solution sol;
  int k = 2;
  int w = 0;
  vector<int> profits = {1, 2, 3};
  vector<int> capital = {0, 1, 1};
  cout << "Test Case 1: " << sol.findMaximizedCapital(k, w, profits, capital)
       << endl; // Expect 4
  return 0;
}
