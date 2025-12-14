#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct DSU {
  vector<int> parent;
  DSU(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
  }
  int find(int x) {
    if (x != parent[x])
      parent[x] = find(parent[x]);
    return parent[x];
  }
  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
      parent[rootX] = rootY;
    }
  }
};

class Solution {
public:
  vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
    unordered_map<string, int> emailToIndex;
    unordered_map<string, string> emailToName;
    int idCount = 0;

    for (const auto &account : accounts) {
      string name = account[0];
      for (int i = 1; i < account.size(); ++i) {
        if (emailToIndex.find(account[i]) == emailToIndex.end()) {
          emailToIndex[account[i]] = idCount++;
          emailToName[account[i]] = name;
        }
      }
    }

    DSU dsu(idCount);

    for (const auto &account : accounts) {
      int firstIdx = emailToIndex[account[1]];
      for (int i = 2; i < account.size(); ++i) {
        dsu.unite(firstIdx, emailToIndex[account[i]]);
      }
    }

    unordered_map<int, vector<string>> components;
    for (auto &pair : emailToIndex) {
      string email = pair.first;
      int idx = pair.second;
      int root = dsu.find(idx);
      components[root].push_back(email);
    }

    vector<vector<string>> result;
    for (auto &pair : components) {
      vector<string> emailList = pair.second;
      sort(emailList.begin(), emailList.end());
      emailList.insert(emailList.begin(), emailToName[emailList[0]]);
      result.push_back(emailList);
    }

    return result;
  }
};

void printAccounts(const vector<vector<string>> &accounts) {
  cout << "[" << endl;
  for (const auto &acc : accounts) {
    cout << "  [";
    for (size_t i = 0; i < acc.size(); ++i) {
      cout << acc[i] << (i < acc.size() - 1 ? ", " : "");
    }
    cout << "]" << endl;
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  vector<vector<string>> accounts = {
      {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
      {"John", "johnsmith@mail.com", "john00@mail.com"},
      {"Mary", "mary@mail.com"},
      {"John", "johnnybravo@mail.com"}};

  vector<vector<string>> res = sol.accountsMerge(accounts);
  printAccounts(res);

  return 0;
}
