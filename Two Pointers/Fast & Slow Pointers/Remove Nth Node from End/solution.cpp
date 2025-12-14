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
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *dummy = new ListNode(0, head);
    ListNode *first = dummy;
    ListNode *second = dummy;

    for (int i = 0; i <= n; i++) {
      first = first->next;
    }

    while (first != nullptr) {
      first = first->next;
      second = second->next;
    }

    ListNode *temp = second->next;
    second->next = second->next->next;
    delete temp;

    return dummy->next;
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

  head = sol.removeNthFromEnd(head, 2);

  cout << "After removing 2nd from end: ";
  printList(head); // Should start with 1->2->3->5
  return 0;
}
