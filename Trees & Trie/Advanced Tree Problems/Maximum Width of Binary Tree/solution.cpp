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
  int widthOfBinaryTree(TreeNode *root) {
    if (!root)
      return 0;

    queue<pair<TreeNode *, unsigned long long>> q;
    q.push({root, 0});
    unsigned long long maxWidth = 0;

    while (!q.empty()) {
      int size = q.size();
      unsigned long long minIndex = q.front().second;
      unsigned long long firstIndex = 0, lastIndex = 0;

      for (int i = 0; i < size; i++) {
        unsigned long long curIndex = q.front().second - minIndex;
        TreeNode *node = q.front().first;
        q.pop();

        if (i == 0)
          firstIndex = curIndex;
        if (i == size - 1)
          lastIndex = curIndex;

        if (node->left)
          q.push({node->left, 2 * curIndex});
        if (node->right)
          q.push({node->right, 2 * curIndex + 1});
      }
      maxWidth = max(maxWidth, lastIndex - firstIndex + 1);
    }
    return (int)maxWidth;
  }
};

int main() {
  Solution sol;
  // [1,3,2,5,3,null,9]
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(3);
  root->right = new TreeNode(2);
  root->left->left = new TreeNode(5);
  root->left->right = new TreeNode(3);
  // null
  root->right->right = new TreeNode(9);

  cout << "Test Case 1: " << sol.widthOfBinaryTree(root) << endl; // Expect 4
  return 0;
}
