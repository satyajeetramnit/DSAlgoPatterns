#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int> &numbers, int target) {
    int left = 0, right = numbers.size() - 1;
    while (left < right) {
      int currentSum = numbers[left] + numbers[right];
      if (currentSum > target) {
        right--;
      } else if (currentSum < target) {
        left++;
      } else {
        return {left + 1, right + 1};
      }
    }
    return {};
  }
};

int main() {
  Solution sol;
  vector<int> numbers = {2, 7, 11, 15};
  int target = 9;
  vector<int> result = sol.twoSum(numbers, target);
  if (result.size() == 2) {
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;
  } else {
    cout << "No solution found" << endl;
  }
  return 0;
}
