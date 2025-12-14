#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder {
private:
  priority_queue<int> small;                            // Max-heap
  priority_queue<int, vector<int>, greater<int>> large; // Min-heap

public:
  MedianFinder() {}

  void addNum(int num) {
    small.push(num);
    large.push(small.top());
    small.pop();

    if (small.size() < large.size()) {
      small.push(large.top());
      large.pop();
    }
  }

  double findMedian() {
    if (small.size() > large.size()) {
      return (double)small.top();
    } else {
      return (double)(small.top() + large.top()) / 2.0;
    }
  }
};

int main() {
  MedianFinder *obj = new MedianFinder();
  obj->addNum(1);
  obj->addNum(2);
  cout << "Median (1,2): " << obj->findMedian() << endl; // 1.5
  obj->addNum(3);
  cout << "Median (1,2,3): " << obj->findMedian() << endl; // 2.0

  delete obj;
  return 0;
}
