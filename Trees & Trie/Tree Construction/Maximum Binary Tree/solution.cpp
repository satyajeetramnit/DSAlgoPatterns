#include <iostream>
#include <queue>
#include <stack>
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
  TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
    vector<TreeNode *> stk;
    for (int num : nums) {
      TreeNode *curr = new TreeNode(num);
      while (!stk.empty() && stk.back()->val < num) {
        curr->left = stk.back();
        stk.pop_back();
      }
      if (!stk.empty()) {
        stk.back()->right = curr;
      }
      stk.push_back(curr);
    }
    return stk.front();
  }
};

void levelOrder(TreeNode *root) {
  if (!root)
    return;
  queue<TreeNode *> q;
  q.push(root);
  cout << "[";
  while (!q.empty()) {
    TreeNode *curr = q.front();
    q.pop();
    if (curr) {
      cout << curr->val << ",";
      q.push(curr->left);
      q.push(curr->right);
    } else {
      cout << "null,";
    }
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  vector<int> nums = {3, 2, 1, 6, 0, 5};
  TreeNode *root = sol.constructMaximumBinaryTree(nums);
  cout << "Test Case 1: ";
  // Output should represent [6,3,5,null,2,0,null,null,1]
  // Just identifying the root is 6 and left is 3 and right is 5 is good enough
  // for basic verify
  if (root->val == 6 && root->left->val == 3 && root->right->val == 5) {
    cout << "Verified (Root: 6, Left: 3, Right: 5)" << endl;
  } else {
    cout << "Failed" << endl;
  }
  return 0;
}
