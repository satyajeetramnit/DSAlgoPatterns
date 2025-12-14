#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode *detectCycle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    bool hasCycle = false;

    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        hasCycle = true;
        break;
      }
    }

    if (!hasCycle)
      return NULL;

    slow = head;
    while (slow != fast) {
      slow = slow->next;
      fast = fast->next;
    }
    return slow;
  }
};

int main() {
  Solution sol;
  // Create list: 3 -> 2 -> 0 -> -4 -> (back to 2)
  ListNode *head = new ListNode(3);
  ListNode *node2 = new ListNode(2);
  ListNode *node0 = new ListNode(0);
  ListNode *node4 = new ListNode(-4);

  head->next = node2;
  node2->next = node0;
  node0->next = node4;
  node4->next = node2; // Cycle

  ListNode *cycleNode = sol.detectCycle(head);
  if (cycleNode) {
    cout << "Cycle detected at node with val: " << cycleNode->val << endl;
  } else {
    cout << "No cycle detected" << endl;
  }

  return 0;
}
