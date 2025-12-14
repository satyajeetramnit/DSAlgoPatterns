#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
  unordered_map<TreeNode *, TreeNode *> parent;

public:
  vector<int> distanceK(TreeNode *root, TreeNode *target, int k) {
    buildParents(root, nullptr);

    queue<TreeNode *> q;
    unordered_set<TreeNode *> visited;

    q.push(target);
    visited.insert(target);

    int current_dist = 0;

    while (!q.empty()) {
      if (current_dist == k) {
        vector<int> result;
        while (!q.empty()) {
          result.push_back(q.front()->val);
          q.pop();
        }
        return result;
      }

      int size = q.size();
      for (int i = 0; i < size; i++) {
        TreeNode *curr = q.front();
        q.pop();

        if (curr->left && !visited.count(curr->left)) {
          q.push(curr->left);
          visited.insert(curr->left);
        }
        if (curr->right && !visited.count(curr->right)) {
          q.push(curr->right);
          visited.insert(curr->right);
        }
        if (parent[curr] && !visited.count(parent[curr])) {
          q.push(parent[curr]);
          visited.insert(parent[curr]);
        }
      }
      current_dist++;
    }

    return {};
  }

  void buildParents(TreeNode *node, TreeNode *par) {
    if (!node)
      return;
    parent[node] = par;
    buildParents(node->left, node);
    buildParents(node->right, node);
  }
};

void printVector(vector<int> v) {
  sort(v.begin(), v.end());
  cout << "[";
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << (i < v.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  // [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(5);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(6);
  root->left->right = new TreeNode(2);
  root->right->left = new TreeNode(0);
  root->right->right = new TreeNode(8);
  root->left->right->left = new TreeNode(7);
  root->left->right->right = new TreeNode(4);

  TreeNode *target = root->left; // 5

  vector<int> result = sol.distanceK(root, target, 2);
  cout << "Test Case 1: ";
  printVector(result); // Expect [1, 4, 7] (sorted order)
  return 0;
}
