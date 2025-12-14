#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class StockSpanner {
  stack<pair<int, int>> st; // {price, span}
public:
  StockSpanner() {}

  int next(int price) {
    int span = 1;
    while (!st.empty() && st.top().first <= price) {
      span += st.top().second;
      st.pop();
    }
    st.push({price, span});
    return span;
  }
};

int main() {
  StockSpanner spanner;
  cout << "100: " << spanner.next(100) << endl; // 1
  cout << "80: " << spanner.next(80) << endl;   // 1
  cout << "60: " << spanner.next(60) << endl;   // 1
  cout << "70: " << spanner.next(70) << endl;   // 2
  cout << "60: " << spanner.next(60) << endl;   // 1
  cout << "75: " << spanner.next(75) << endl;   // 4
  cout << "85: " << spanner.next(85) << endl;   // 6
  return 0;
}
