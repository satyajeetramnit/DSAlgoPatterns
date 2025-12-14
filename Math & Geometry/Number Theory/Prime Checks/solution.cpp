#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  bool isPrime(int n) {
    if (n <= 1)
      return false;
    if (n <= 3)
      return true;
    if (n % 2 == 0 || n % 3 == 0)
      return false;
    for (int i = 5; i * i <= n; i += 6) {
      if (n % i == 0 || n % (i + 2) == 0)
        return false;
    }
    return true;
  }

  int countPrimes(int n) {
    if (n <= 2)
      return 0;
    vector<bool> is_prime(n, true);
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p * p < n; ++p) {
      if (is_prime[p]) {
        for (int i = p * p; i < n; i += p) {
          is_prime[i] = false;
        }
      }
    }

    int count = 0;
    for (int i = 2; i < n; ++i) {
      if (is_prime[i])
        count++;
    }
    return count;
  }
};

int main() {
  Solution sol;
  cout << boolalpha;
  cout << "Test Case 1 (10): " << sol.countPrimes(10) << endl; // 4 (2,3,5,7)
  cout << "Test Case 2 (1): " << sol.countPrimes(1) << endl;   // 0
  cout << "Is 29 prime? " << sol.isPrime(29) << endl;          // true
  return 0;
}
