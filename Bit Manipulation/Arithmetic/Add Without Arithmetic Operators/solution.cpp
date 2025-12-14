#include <iostream>

using namespace std;

class Solution {
public:
  int getSum(int a, int b) {
    while (b != 0) {
      unsigned int carry = (unsigned int)(a & b) << 1;
      a = a ^ b;
      b = carry;
    }
    return a;
  }
};

int main() {
  Solution sol;
  cout << "Test Case 1 (1 + 2): " << sol.getSum(1, 2) << endl;   // Expect 3
  cout << "Test Case 2 (-2 + 3): " << sol.getSum(-2, 3) << endl; // Expect 1
  return 0;
}
