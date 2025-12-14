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
  bool isPalindrome(ListNode *head) {
    if (!head || !head->next)
      return true;

    // Find middle
    ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) {
      slow = slow->next;
      fast = fast->next->next;
    }

    // Reverse second half
    ListNode *secondHalf = reverseList(slow->next);
    ListNode *firstHalf = head;

    // Check palindrome
    ListNode *p1 = firstHalf;
    ListNode *p2 = secondHalf;
    bool result = true;
    while (result && p2) {
      if (p1->val != p2->val)
        result = false;
      p1 = p1->next;
      p2 = p2->next;
    }

    // Restore list
    slow->next = reverseList(secondHalf);
    return result;
  }

  ListNode *reverseList(ListNode *head) {
    ListNode *prev = nullptr, *curr = head;
    while (curr) {
      ListNode *nextTemp = curr->next;
      curr->next = prev;
      prev = curr;
      curr = nextTemp;
    }
    return prev;
  }
};

int main() {
  Solution sol;

  // 1 -> 2 -> 2 -> 1
  ListNode *head =
      new ListNode(1, new ListNode(2, new ListNode(2, new ListNode(1))));
  bool isPal = sol.isPalindrome(head);
  cout << "Is Palindrome (1->2->2->1): " << (isPal ? "true" : "false") << endl;

  // 1 -> 2
  ListNode *head2 = new ListNode(1, new ListNode(2));
  isPal = sol.isPalindrome(head2);
  cout << "Is Palindrome (1->2): " << (isPal ? "true" : "false") << endl;

  return 0;
}
