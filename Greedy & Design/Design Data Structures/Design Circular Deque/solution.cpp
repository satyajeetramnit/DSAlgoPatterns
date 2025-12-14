#include <iostream>
#include <vector>

using namespace std;

class MyCircularDeque {
  vector<int> buffer;
  int k;
  int front; // Points to current front
  int rear;  // Points to current rear
  int count; // To track size

public:
  MyCircularDeque(int k) {
    this->k = k;
    buffer.resize(k);
    front = 0;
    rear = k - 1; // Start rear "behind" front effectively
    count = 0;
  }

  bool insertFront(int value) {
    if (isFull())
      return false;
    front = (front - 1 + k) % k;
    buffer[front] = value;
    count++;
    return true;
  }

  bool insertLast(int value) {
    if (isFull())
      return false;
    rear = (rear + 1) % k;
    buffer[rear] = value;
    count++;
    return true;
  }

  bool deleteFront() {
    if (isEmpty())
      return false;
    front = (front + 1) % k;
    count--;
    return true;
  }

  bool deleteLast() {
    if (isEmpty())
      return false;
    rear = (rear - 1 + k) % k;
    count--;
    return true;
  }

  int getFront() {
    if (isEmpty())
      return -1;
    return buffer[front];
  }

  int getRear() {
    if (isEmpty())
      return -1;
    return buffer[rear];
  }

  bool isEmpty() { return count == 0; }

  bool isFull() { return count == k; }
};

int main() {
  MyCircularDeque deque(3);
  cout << "Insert Last 1: " << deque.insertLast(1) << endl;   // true
  cout << "Insert Last 2: " << deque.insertLast(2) << endl;   // true
  cout << "Insert Front 3: " << deque.insertFront(3) << endl; // true. [3, 1, 2]
  cout << "Insert Front 4 (Full): " << deque.insertFront(4) << endl; // false
  cout << "Get Rear (2): " << deque.getRear() << endl;               // 2
  cout << "Is Full (1): " << deque.isFull() << endl;                 // 1
  cout << "Delete Last: " << deque.deleteLast() << endl; // true. [3, 1]
  cout << "Get Front (3): " << deque.getFront() << endl; // 3
  return 0;
}
