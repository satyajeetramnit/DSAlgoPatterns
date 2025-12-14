#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *reverseList(ListNode *head) {
    ListNode *prev = nullptr;
    ListNode *curr = head;
    while (curr) {
      ListNode *nextTemp = curr->next;
      curr->next = prev;
      prev = curr;
      curr = nextTemp;
    }
    return prev;
  }
};

void printList(ListNode *head) {
  while (head) {
    cout << head->val << (head->next ? "->" : "");
    head = head->next;
  }
  cout << endl;
}

int main() {
  Solution sol;
  ListNode *head = new ListNode(
      1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
  cout << "Original: ";
  printList(head);

  head = sol.reverseList(head);

  cout << "Reversed: ";
  printList(head);
  return 0;
}
