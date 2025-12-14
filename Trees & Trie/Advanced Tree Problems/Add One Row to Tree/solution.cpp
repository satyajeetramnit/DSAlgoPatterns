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
  TreeNode *addOneRow(TreeNode *root, int val, int depth) {
    if (depth == 1) {
      TreeNode *newRoot = new TreeNode(val);
      newRoot->left = root;
      return newRoot;
    }

    queue<TreeNode *> q;
    q.push(root);
    int currentDepth = 1;

    while (!q.empty()) {
      int size = q.size();

      // If we are at the parent level (depth - 1)
      if (currentDepth == depth - 1) {
        for (int i = 0; i < size; i++) {
          TreeNode *node = q.front();
          q.pop();

          TreeNode *oldLeft = node->left;
          TreeNode *oldRight = node->right;

          node->left = new TreeNode(val);
          node->right = new TreeNode(val);

          node->left->left = oldLeft;
          node->right->right = oldRight;
        }
        break; // Done
      }

      for (int i = 0; i < size; i++) {
        TreeNode *node = q.front();
        q.pop();
        if (node->left)
          q.push(node->left);
        if (node->right)
          q.push(node->right);
      }
      currentDepth++;
    }

    return root;
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
  // [4,2,6,3,1,5], val = 1, depth = 2
  TreeNode *root = new TreeNode(4);
  root->left = new TreeNode(2);
  root->right = new TreeNode(6);
  root->left->left = new TreeNode(3);
  root->left->right = new TreeNode(1);
  root->right->left = new TreeNode(5);

  TreeNode *res = sol.addOneRow(root, 1, 2);
  cout << "Test Case 1: ";
  // Expected level order conceptually: [4,1,1,2,null,null,6,3,1,5]
  // 4 -> left:1, right:1
  // left:1 -> left:2
  // right:1 -> right:6
  if (res->val == 4 && res->left->val == 1 && res->right->val == 1 &&
      res->left->left->val == 2) {
    cout << "Verified (4 -> 1,1 -> 2 ...)" << endl;
  } else {
    cout << "Failed" << endl;
  }
  return 0;
}
