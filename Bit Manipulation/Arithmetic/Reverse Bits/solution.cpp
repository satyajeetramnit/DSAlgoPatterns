#include <bitset>
#include <cstdint>
#include <iostream>

using namespace std;

class Solution {
public:
  uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    for (int i = 0; i < 32; ++i) {
      if ((n >> i) & 1) {
        res |= (1 << (31 - i));
      }
    }
    return res;
  }
};

int main() {
  Solution sol;

  // Case 1: 43261596 (binary 00000010100101000001111010011100)
  // Expected: 964176192 (00111001011110000010100101000000)
  uint32_t n1 = 43261596;
  cout << "Test Case 1: " << sol.reverseBits(n1) << endl;

  // Case 2: 11111111111111111111111111111101 (binary ending in 01, should start
  // with 10 then 1s) -3 in 2's complement (32 bit) is ...111101 Unsigned
  // literal
  uint32_t n2 = 4294967293;
  cout << "Test Case 2: " << sol.reverseBits(n2) << endl;

  return 0;
}
