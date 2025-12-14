#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class NumArray {
  vector<int> tree;
  int n;

  void build(vector<int> &nums, int node, int start, int end) {
    if (start == end) {
      tree[node] = nums[start];
    } else {
      int mid = (start + end) / 2;
      build(nums, 2 * node, start, mid);
      build(nums, 2 * node + 1, mid + 1, end);
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
      tree[node] = val;
    } else {
      int mid = (start + end) / 2;
      if (start <= idx && idx <= mid) {
        update(2 * node, start, mid, idx, val);
      } else {
        update(2 * node + 1, mid + 1, end, idx, val);
      }
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
  }

  int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
      return 0; // Out of range
    }
    if (l <= start && end <= r) {
      return tree[node]; // Fully in range
    }
    int mid = (start + end) / 2;
    int p1 = query(2 * node, start, mid, l, r);
    int p2 = query(2 * node + 1, mid + 1, end, l, r);
    return p1 + p2;
  }

public:
  NumArray(vector<int> &nums) {
    n = nums.size();
    if (n > 0) {
      tree.resize(4 * n);
      build(nums, 1, 0, n - 1);
    }
  }

  void update(int index, int val) {
    if (n > 0)
      update(1, 0, n - 1, index, val);
  }

  int sumRange(int left, int right) {
    if (n > 0)
      return query(1, 0, n - 1, left, right);
    return 0;
  }
};

int main() {
  vector<int> nums = {1, 3, 5};
  NumArray *obj = new NumArray(nums);

  // Test 1: Sum Range (0, 2) -> 1 + 3 + 5 = 9
  assert(obj->sumRange(0, 2) == 9);
  cout << "Test 1 Passed" << endl;

  // Test 2: Update (1, 2) -> [1, 2, 5]
  obj->update(1, 2);

  // Test 3: Sum Range (0, 2) -> 1 + 2 + 5 = 8
  assert(obj->sumRange(0, 2) == 8);
  cout << "Test 3 Passed" << endl;

  delete obj;
  return 0;
}
