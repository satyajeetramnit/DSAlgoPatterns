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
  ListNode *swapPairs(ListNode *head) {
    ListNode *dummy = new ListNode(0, head);
    ListNode *prev = dummy;
    ListNode *curr = head;

    while (curr && curr->next) {
      ListNode *nextPair = curr->next->next;
      ListNode *second = curr->next;

      // Swap
      second->next = curr;
      curr->next = nextPair;
      prev->next = second;

      // Advance
      prev = curr;
      curr = nextPair;
    }
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
  ListNode *head =
      new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
  cout << "Original: ";
  printList(head);

  head = sol.swapPairs(head);

  cout << "Swapped: ";
  printList(head); // 2->1->4->3
  return 0;
}
