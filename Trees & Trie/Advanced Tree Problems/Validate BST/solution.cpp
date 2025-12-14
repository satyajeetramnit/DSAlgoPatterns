#include <climits>
#include <iostream>
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
  bool isValidBST(TreeNode *root) { return validate(root, LONG_MIN, LONG_MAX); }

  bool validate(TreeNode *node, long minVal, long maxVal) {
    if (!node)
      return true;

    if (node->val <= minVal || node->val >= maxVal)
      return false;

    return validate(node->left, minVal, node->val) &&
           validate(node->right, node->val, maxVal);
  }
};

int main() {
  Solution sol;
  // [2,1,3]
  TreeNode *root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(3);

  cout << "Test Case 1: " << boolalpha << sol.isValidBST(root)
       << endl; // Expect true
  return 0;
}
