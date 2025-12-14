#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class KthLargest {
private:
  priority_queue<int, vector<int>, greater<int>> minHeap;
  int k;

public:
  KthLargest(int k, vector<int> &nums) {
    this->k = k;
    for (int num : nums) {
      minHeap.push(num);
      if (minHeap.size() > k) {
        minHeap.pop();
      }
    }
  }

  int add(int val) {
    minHeap.push(val);
    if (minHeap.size() > k) {
      minHeap.pop();
    }
    return minHeap.top();
  }
};

int main() {
  vector<int> nums = {4, 5, 8, 2};
  KthLargest *obj = new KthLargest(3, nums);
  cout << "Test Case 1:" << endl;
  cout << "Add 3: " << obj->add(3) << endl;   // 4
  cout << "Add 5: " << obj->add(5) << endl;   // 5
  cout << "Add 10: " << obj->add(10) << endl; // 5
  cout << "Add 9: " << obj->add(9) << endl;   // 8
  cout << "Add 4: " << obj->add(4) << endl;   // 8

  delete obj;
  return 0;
}
