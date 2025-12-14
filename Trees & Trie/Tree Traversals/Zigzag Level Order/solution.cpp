#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
    vector<vector<int>> result;
    if (!root)
      return result;

    queue<TreeNode *> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty()) {
      int size = q.size();
      vector<int> level(size);

      for (int i = 0; i < size; i++) {
        TreeNode *node = q.front();
        q.pop();

        int index = leftToRight ? i : (size - 1 - i);
        level[index] = node->val;

        if (node->left)
          q.push(node->left);
        if (node->right)
          q.push(node->right);
      }
      leftToRight = !leftToRight;
      result.push_back(level);
    }

    return result;
  }
};

void printResult(const vector<vector<int>> &result) {
  cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    cout << "[";
    for (size_t j = 0; j < result[i].size(); ++j) {
      cout << result[i][j] << (j < result[i].size() - 1 ? "," : "");
    }
    cout << "]" << (i < result.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  // [3,9,20,null,null,15,7]
  TreeNode *root = new TreeNode(3);
  root->left = new TreeNode(9);
  root->right = new TreeNode(20);
  root->right->left = new TreeNode(15);
  root->right->right = new TreeNode(7);

  vector<vector<int>> result = sol.zigzagLevelOrder(root);
  cout << "Test Case 1: ";
  printResult(result); // Expect [[3],[20,9],[15,7]]
  return 0;
}
