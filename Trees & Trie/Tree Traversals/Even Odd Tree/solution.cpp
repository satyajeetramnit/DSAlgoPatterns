#include <climits>
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
  bool isEvenOddTree(TreeNode *root) {
    if (!root)
      return true;
    queue<TreeNode *> q;
    q.push(root);
    int level = 0;

    while (!q.empty()) {
      int size = q.size();
      int prev_val = (level % 2 == 0) ? INT_MIN : INT_MAX;

      for (int i = 0; i < size; i++) {
        TreeNode *node = q.front();
        q.pop();

        // Check parity
        if (level % 2 == 0) { // Even level: odd vals, increasing
          if (node->val % 2 == 0 || node->val <= prev_val)
            return false;
        } else { // Odd level: even vals, decreasing
          if (node->val % 2 != 0 || node->val >= prev_val)
            return false;
        }

        prev_val = node->val;

        if (node->left)
          q.push(node->left);
        if (node->right)
          q.push(node->right);
      }
      level++;
    }
    return true;
  }
};

int main() {
  Solution sol;
  // [1,10,4,3,null,7,9,12,8,6,null,null,2]
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(10);
  root->right = new TreeNode(4);

  root->left->left = new TreeNode(3);
  root->right->left = new TreeNode(7);
  root->right->right = new TreeNode(9);

  root->left->left->left = new TreeNode(12);
  root->left->left->right = new TreeNode(8);
  root->right->left->left = new TreeNode(6);
  root->right->right->right = new TreeNode(2);

  cout << "Test Case 1: " << boolalpha << sol.isEvenOddTree(root)
       << endl; // Expect true
  return 0;
}
