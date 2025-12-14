#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
  struct compare {
    bool operator()(const ListNode *l, const ListNode *r) {
      return l->val > r->val;
    }
  };

public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    priority_queue<ListNode *, vector<ListNode *>, compare> pq;
    for (auto l : lists) {
      if (l)
        pq.push(l);
    }

    ListNode dummy(0);
    ListNode *tail = &dummy;

    while (!pq.empty()) {
      ListNode *node = pq.top();
      pq.pop();
      tail->next = node;
      tail = tail->next;

      if (node->next)
        pq.push(node->next);
    }

    return dummy.next;
  }
};

void printList(ListNode *head) {
  while (head) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;
}

int main() {
  Solution sol;

  // List 1: 1->4->5
  ListNode *l1 = new ListNode(1);
  l1->next = new ListNode(4);
  l1->next->next = new ListNode(5);

  // List 2: 1->3->4
  ListNode *l2 = new ListNode(1);
  l2->next = new ListNode(3);
  l2->next->next = new ListNode(4);

  // List 3: 2->6
  ListNode *l3 = new ListNode(2);
  l3->next = new ListNode(6);

  vector<ListNode *> lists = {l1, l2, l3};
  ListNode *merged = sol.mergeKLists(lists);

  cout << "Test Case 1: ";
  printList(merged); // Expect 1 1 2 3 4 4 5 6

  return 0;
}
