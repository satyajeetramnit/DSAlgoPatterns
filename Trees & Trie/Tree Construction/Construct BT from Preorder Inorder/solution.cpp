#include <algorithm>
#include <iostream>
#include <unordered_map>
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
  unordered_map<int, int> inorder_map;
  int pre_idx = 0;

public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    pre_idx = 0;
    inorder_map.clear();
    for (int i = 0; i < inorder.size(); i++) {
      inorder_map[inorder[i]] = i;
    }
    return build(preorder, 0, inorder.size() - 1);
  }

  TreeNode *build(vector<int> &preorder, int in_left, int in_right) {
    if (in_left > in_right)
      return nullptr;

    int root_val = preorder[pre_idx++];
    TreeNode *root = new TreeNode(root_val);

    int index = inorder_map[root_val];

    root->left = build(preorder, in_left, index - 1);
    root->right = build(preorder, index + 1, in_right);

    return root;
  }
};

// Helper for verifying
void preorderTraversal(TreeNode *root, vector<int> &res) {
  if (!root)
    return;
  res.push_back(root->val);
  preorderTraversal(root->left, res);
  preorderTraversal(root->right, res);
}

void printVector(const vector<int> &v) {
  cout << "[";
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << (i < v.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution sol;
  vector<int> preorder = {3, 9, 20, 15, 7};
  vector<int> inorder = {9, 3, 15, 20, 7};
  TreeNode *root = sol.buildTree(preorder, inorder);

  vector<int> res;
  preorderTraversal(root, res);
  cout << "Test Case 1 (Re-Preorder): ";
  printVector(res); // Expect [3,9,20,15,7]
  return 0;
}
