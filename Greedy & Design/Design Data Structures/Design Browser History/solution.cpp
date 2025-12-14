#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BrowserHistory {
  vector<string> history;
  int curr, limit;

public:
  BrowserHistory(string homepage) {
    history.push_back(homepage);
    curr = 0;
    limit = 0;
  }

  void visit(string url) {
    curr++;
    if (curr < history.size()) {
      history[curr] = url;
    } else {
      history.push_back(url);
    }
    limit = curr;
  }

  string back(int steps) {
    curr = max(0, curr - steps);
    return history[curr];
  }

  string forward(int steps) {
    curr = min(limit, curr + steps);
    return history[curr];
  }
};

int main() {
  BrowserHistory bh("leetcode.com");
  bh.visit("google.com");   // You are in "leetcode.com". Visit "google.com"
  bh.visit("facebook.com"); // Visit "facebook.com"
  bh.visit("youtube.com");  // Visit "youtube.com"
  cout << "Back 1 (Expect facebook.com): " << bh.back(1) << endl;
  cout << "Back 1 (Expect google.com): " << bh.back(1) << endl;
  cout << "Forward 1 (Expect facebook.com): " << bh.forward(1) << endl;
  bh.visit("linkedin.com"); // Visit "linkedin.com". Clears forward history
                            // (youtube.com)
  cout << "Forward 2 (Expect linkedin.com): " << bh.forward(2)
       << endl; // Cannot move forward
  cout << "Back 2 (Expect google.com): " << bh.back(2) << endl;
  cout << "Back 7 (Expect leetcode.com): " << bh.back(7) << endl;
  return 0;
}
