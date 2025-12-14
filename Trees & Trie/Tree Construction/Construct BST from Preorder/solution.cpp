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
  int idx = 0;

public:
  TreeNode *bstFromPreorder(vector<int> &preorder) {
    idx = 0;
    return build(preorder, INT_MAX);
  }

  TreeNode *build(vector<int> &preorder, int bound) {
    if (idx >= preorder.size() || preorder[idx] > bound) {
      return nullptr;
    }

    TreeNode *root = new TreeNode(preorder[idx++]);
    root->left = build(preorder, root->val);
    root->right = build(preorder, bound);

    return root;
  }
};

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
  vector<int> preorder = {8, 5, 1, 7, 10, 12};
  TreeNode *root = sol.bstFromPreorder(preorder);

  vector<int> res;
  preorderTraversal(root, res);
  cout << "Test Case 1 (Re-Preorder): ";
  printVector(res); // Expect [8, 5, 1, 7, 10, 12]
  return 0;
}
