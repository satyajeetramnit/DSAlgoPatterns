#include <iostream>

using namespace std;

class Solution {
public:
  bool isPowerOfTwo(int n) {
    if (n <= 0)
      return false;
    // Cast to long long literal 1ll to ensure subtraction promotion handles
    // cases correctly if passed roughly or just to match implementation
    // pattern. For standard int, n-1 is fine.
    return (n & (long long)n - 1) == 0;
  }
};

int main() {
  Solution sol;
  cout << boolalpha;
  cout << "Test Case 1 (1): " << sol.isPowerOfTwo(1) << endl;   // true
  cout << "Test Case 2 (16): " << sol.isPowerOfTwo(16) << endl; // true
  cout << "Test Case 3 (3): " << sol.isPowerOfTwo(3) << endl;   // false
  return 0;
}
