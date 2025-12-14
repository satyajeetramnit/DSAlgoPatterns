#include <cstdlib>
#include <iostream>

using namespace std;

class Solution {
public:
  int gcd(int a, int b) {
    while (b != 0) {
      int temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }

  long long lcm(int a, int b) {
    if (a == 0 || b == 0)
      return 0;
    return (1LL * abs(a) / gcd(a, b)) * abs(b);
  }
};

int main() {
  Solution sol;
  cout << "Test Case 1 (12, 18): GCD=" << sol.gcd(12, 18)
       << ", LCM=" << sol.lcm(12, 18) << endl; // 6, 36
  cout << "Test Case 2 (5, 7): GCD=" << sol.gcd(5, 7)
       << ", LCM=" << sol.lcm(5, 7) << endl; // 1, 35
  return 0;
}
