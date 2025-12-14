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
  ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode *dummy = new ListNode(0, head);
    ListNode *groupPrev = dummy;

    while (true) {
      ListNode *kth = getKth(groupPrev, k);
      if (!kth)
        break;
      ListNode *groupNext = kth->next;

      // Reverse group
      ListNode *prev = kth->next;
      ListNode *curr = groupPrev->next;

      while (curr != groupNext) {
        ListNode *tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
      }

      ListNode *tmp = groupPrev->next;
      groupPrev->next = kth;
      groupPrev = tmp;
    }
    return dummy->next;
  }

  ListNode *getKth(ListNode *curr, int k) {
    while (curr && k > 0) {
      curr = curr->next;
      k--;
    }
    return curr;
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

  head = sol.reverseKGroup(head, 2);

  cout << "Reversed k=2: ";
  printList(head); // 2->1->4->3->5
  return 0;
}
