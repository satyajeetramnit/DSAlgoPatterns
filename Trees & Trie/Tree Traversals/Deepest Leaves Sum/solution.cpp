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
  int deepestLeavesSum(TreeNode *root) {
    if (!root)
      return 0;
    queue<TreeNode *> q;
    q.push(root);
    int sum = 0;

    while (!q.empty()) {
      int size = q.size();
      sum = 0; // Reset sum for new level

      for (int i = 0; i < size; i++) {
        TreeNode *node = q.front();
        q.pop();
        sum += node->val;

        if (node->left)
          q.push(node->left);
        if (node->right)
          q.push(node->right);
      }
    }

    return sum; // Returns sum of last level processed
  }
};

int main() {
  Solution sol;
  // [1,2,3,4,5,null,6,7,null,null,null,null,8]
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->right = new TreeNode(6);
  root->left->left->left = new TreeNode(7);
  root->right->right->right = new TreeNode(8);

  // Deepest leaves are 7 and 8. Sum = 15.
  cout << "Test Case 1: " << sol.deepestLeavesSum(root) << endl; // Expect 15
  return 0;
}
