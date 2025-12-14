#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  int leastInterval(vector<char> &tasks, int n) {
    unordered_map<char, int> counts;
    for (char t : tasks)
      counts[t]++;

    priority_queue<int> maxHeap;
    for (auto &pair : counts)
      maxHeap.push(pair.second);

    int time = 0;
    queue<pair<int, int>> q; // {freq, active_time}

    while (!maxHeap.empty() || !q.empty()) {
      time++;

      if (!maxHeap.empty()) {
        int freq = maxHeap.top();
        maxHeap.pop();
        freq--;
        if (freq > 0) {
          q.push({freq, time + n});
        }
      }

      if (!q.empty() && q.front().second == time) {
        maxHeap.push(q.front().first);
        q.pop();
      }
    }

    return time;
  }
};

int main() {
  Solution sol;
  vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
  int n = 2;
  cout << "Test Case 1: " << sol.leastInterval(tasks, n) << endl; // Expect 8

  return 0;
}
